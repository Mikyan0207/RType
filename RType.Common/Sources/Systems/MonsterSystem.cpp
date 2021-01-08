#include <Systems/MonsterSystem.hpp>
#include <Entities/Entity.hpp>

MonsterSystem::MonsterSystem(const std::size_t& id, const Pointer<GameManager> gameManager) : System<Monster>("MonsterSystem#" + std::to_string(id))
{
	m_GameManager = gameManager;
}

void MonsterSystem::Update(const double& deltaTime)
{
	for (auto &&component : m_Components)
	{
		auto* monster = std::get<Pointer<Monster>>(component);
		const auto& interface = monster->GetIMonster();
		const auto& bullet_to_update = monster->Shoot();
		const auto& bullet_vector = interface->GetBulletsPosition();

		const auto& file = interface->GetBulletFilename();
		if (bullet_to_update.has_value())
			for (auto && [id, pos] : bullet_to_update.value())
			{
				LoadBullets(file, id, pos);
			}

		for (auto&& [id, pos] : bullet_vector)
		{
			if (pos.first < -20.0f)
			{
				Destroy(id);
				interface->RemoveBullet(id);
			}
		}

		UpdateBullets(bullet_vector);

		interface->Update();

		if (interface->GetPosition().first < -20.0f)
		{
			Destroy(monster);
			m_GameManager->RemoveMonsterId(monster->GetEntityId());
			m_GameManager->RemoveEntity(monster->GetEntityId());
			return;
		}

		// TODO: Set Entity Id based on monster Id + x instance of the monster.
		UpdateMonster(static_cast<uint32_t>(monster->GetEntityId()), interface->GetPosition());
	}
}

void MonsterSystem::OnEvent(sf::Event& event)
{
}

void MonsterSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.code() == RType::RGamePack::COLLISION)
	{
		auto content = pack.collidepacket();
		for (const auto & id : content.ids())
		{
			auto* e1 = m_GameManager->GetIEntity(id);

			if (!e1)
				continue;
			auto monster = e1->AsEntity()->GetComponent<Monster>();
			if (monster.has_value())
			{
				m_GameManager->RemoveMonsterId(e1->GetId());
			}
		}
	}
}

void MonsterSystem::UpdateMonster(const uint32_t& monsterId, const std::pair<float, float>& position) const
{
	auto wrapper = RType::RGamePack();
	auto* positionPacket = new RType::PositionPacket();
	wrapper.set_code(RType::RGamePack::POSITION);

	positionPacket->add_id(monsterId);
	auto* vector2 = positionPacket->add_position();
	vector2->set_x(static_cast<double>(position.first));
	vector2->set_y(static_cast<double>(position.second));

	wrapper.set_allocated_positioncontent(positionPacket);

	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
}

void MonsterSystem::LoadBullets(const std::string& filename, const uint32_t& bulletId, const std::pair<float, float>& position) const
{
	auto wrapper = RType::RGamePack();
	auto* load = new RType::LoadPacket();
	auto* vector2 = new RType::Vector2();

	wrapper.set_code(RType::RGamePack::LOAD);

	vector2->set_x(static_cast<double>(position.first));
	vector2->set_y(static_cast<double>(position.second));

	load->set_type(RType::LoadPacket::ENEMY_BULLET);
	load->set_filename(filename);
	load->set_id(bulletId);
	load->set_allocated_position(vector2);

	wrapper.set_allocated_loadcontent(load);

	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
}

void MonsterSystem::UpdateBullets(const std::vector<std::pair<uint32_t, std::pair<float, float>>>& bullets) const
{
	auto wrapper = RType::RGamePack();
	auto* positionPacket = new RType::PositionPacket();

	wrapper.set_code(RType::RGamePack::POSITION);

	for (auto && [id, pos] : bullets)
	{
		positionPacket->add_id(id);
		auto* vector2 = positionPacket->add_position();

		vector2->set_x(static_cast<double>(pos.first));
		vector2->set_y(static_cast<double>(pos.second));
	}

	wrapper.set_allocated_positioncontent(positionPacket);
	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
}

void MonsterSystem::Destroy(Pointer<Monster> monster) const
{
	auto wrapper = RType::RGamePack();
	auto *destroy = new RType::DestroyPacket();

	wrapper.set_code(RType::RGamePack::DESTROY);

	destroy->add_ids(static_cast<uint32_t>(monster->GetEntityId()));

	wrapper.set_allocated_destroycontent(destroy);
	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);

	auto wrapper2 = RType::RGamePack();
	auto* position = new RType::PositionPacket();
	wrapper2.set_code(RType::RGamePack::POSITION);
	position->set_has_velocity(true);
	for (auto && [id, pos] : monster->GetIMonster()->GetBulletsPosition())
	{
		position->add_id(id);
		position->add_velocity(-20);
	}
	wrapper2.set_allocated_positioncontent(position);
	m_GameManager->GetUdpNetwork()->SendAsync(wrapper2);
}

void MonsterSystem::Destroy(const size_t& id) const
{
	auto wrapper = RType::RGamePack();
	auto* destroy = new RType::DestroyPacket();

	wrapper.set_code(RType::RGamePack::DESTROY);

	destroy->add_ids(static_cast<uint32_t>(id));

	wrapper.set_allocated_destroycontent(destroy);
	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
}