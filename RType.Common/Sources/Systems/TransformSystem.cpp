#include <Systems/TransformSystem.hpp>
#include <Entities/Entity.hpp>
#include <Logger.hpp>

TransformSystem::TransformSystem(const std::size_t& id, const Pointer<GameManager> gameManager) : System<Transform>("TransformSystem#" + std::to_string(id))
{
	m_GameManager = gameManager;
}

void TransformSystem::Update(const double& deltaTime)
{
	for (auto && component : m_Components)
	{
		auto* transform = std::get<Pointer<Transform>>(component);

		if (transform->GetEntityId() <= 4)
		{
			continue;
		}
		auto pos = transform->GetPosition();
		
		transform->SetPosition({
			pos.x + static_cast<float>(transform->GetVelocity() * deltaTime),
			pos.y
		});

		if (transform->GetEntityId() >= 8000 &&
		(transform->GetPosition().x < 0 || transform->GetPosition().x > 2000))
		{
			auto wrapper = RType::RGamePack();
			auto* content = new RType::DestroyPacket();

			wrapper.set_code(RType::RGamePack::DESTROY);
			content->add_ids(transform->GetEntityId());
			wrapper.set_allocated_destroycontent(content);

			SendToPlayers(wrapper);
			m_GameManager->RemoveEntity(transform->GetEntityId());
		}
	}
}

void TransformSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.code() == RType::RGamePack::POSITION)
	{
		if (!pack.has_positioncontent())
			return;

		const auto& positionContent = pack.positioncontent();
		for (auto i = 0; i < positionContent.id_size(); ++i)
		{
			auto* entity = m_GameManager->GetIEntity(positionContent.id()[i]);

			if (!entity)
				continue;

			auto component = entity->AsEntity()->GetComponent<Transform>();

			if (component.has_value())
			{
				component.value()->SetPosition({
					static_cast<float>(positionContent.position()[i].x()),
					static_cast<float>(positionContent.position()[i].y())
				});
			}
		}
	}
	else if (pack.code() == RType::RGamePack::ACTION)
	{
		if (!pack.has_actioncontent())
			return;

		const auto& actionContent = pack.actioncontent();
		auto* entity = m_GameManager->GetIEntity(actionContent.id());

		if (!entity)
			return;

		auto component = entity->AsEntity()->GetComponent<Transform>();

		if (component.has_value())
		{
			const auto& currentPosition = component.value()->GetPosition();

			auto wrapper = RType::RGamePack();
			auto* position = new RType::PositionPacket();
			auto* vector2 = new RType::Vector2();

			switch (actionContent.type())
			{
				case RType::ActionPacket::UP:
				{
					component.value()->SetPosition({currentPosition.x, currentPosition.y - (2.0f)});

					position->add_id(actionContent.id());
					auto *posToFill = position->add_position();
					posToFill->set_x(currentPosition.x);
					posToFill->set_y(currentPosition.y - 2.0f);
					wrapper.set_code(RType::RGamePack::POSITION);
					wrapper.set_playerid(actionContent.id());
					wrapper.set_allocated_positioncontent(position);

					SendToPlayers(wrapper);
				} break;
				case RType::ActionPacket::DOWN:
				{
					component.value()->SetPosition({ currentPosition.x, currentPosition.y + (2.0f) });

					position->add_id(actionContent.id());
					auto* posToFill = position->add_position();
					posToFill->set_x(currentPosition.x);
					posToFill->set_y(currentPosition.y + 2.0f);
					wrapper.set_code(RType::RGamePack::POSITION);
					wrapper.set_playerid(actionContent.id());
					wrapper.set_allocated_positioncontent(position);
					
					SendToPlayers(wrapper);
				} break;
				case RType::ActionPacket::LEFT:
				{
					component.value()->SetPosition({ currentPosition.x - (2.0f), currentPosition.y });

					position->add_id(actionContent.id());
					auto* posToFill = position->add_position();
					posToFill->set_x(currentPosition.x - 2.0f);
					posToFill->set_y(currentPosition.y);
					wrapper.set_code(RType::RGamePack::POSITION);
					wrapper.set_playerid(actionContent.id());
					wrapper.set_allocated_positioncontent(position);

					SendToPlayers(wrapper);
				} break;
				case RType::ActionPacket::RIGHT:
				{
					component.value()->SetPosition({ currentPosition.x + (2.0f), currentPosition.y });

					position->add_id(actionContent.id());
					auto* posToFill = position->add_position();
					posToFill->set_x(currentPosition.x + 2.0f);
					posToFill->set_y(currentPosition.y);
					wrapper.set_code(RType::RGamePack::POSITION);
					wrapper.set_playerid(actionContent.id());
					wrapper.set_allocated_positioncontent(position);

					SendToPlayers(wrapper);
				} break;
				case RType::ActionPacket::SHOOT:
				{
					static size_t SHOOT_ID = 8000;
					if (SHOOT_ID > 8999)
						SHOOT_ID = 8000;

					auto bullet = CreateUnique<Entity>(SHOOT_ID++);
					auto* bulletTransform = new Transform({currentPosition.x + 25.0f, currentPosition.y + 9.0f});
						
					bulletTransform->SetVelocity(2.0);
					bullet->AddComponent(bulletTransform, Transform::Id);
					{
						auto* createPack = new RType::LoadPacket();

						wrapper.set_code(RType::RGamePack::LOAD);
						vector2->set_x(currentPosition.x + 25.0f);
						vector2->set_y(currentPosition.y + 9.0f);
						createPack->set_id(bullet->GetId());
						createPack->set_type(RType::LoadPacket::BASIC_SHOT);
						createPack->set_filename("shoot_" + std::to_string(actionContent.shootlevel()) + ".png");
						createPack->set_allocated_position(vector2);
						wrapper.set_allocated_loadcontent(createPack);

						SendToPlayers(wrapper);
					}
					m_GameManager->AddEntity(std::move(bullet));
				} break;
				default:
				{
					// Ignore.
				} break;
			}
		}
	}
}

void TransformSystem::SendToPlayer(RType::RGamePack& pack, const std::size_t& playerId) const
{
	m_GameManager->GetUdpNetwork()->SendAsync(pack, playerId);
}

void TransformSystem::SendToPlayers(RType::RGamePack& pack) const
{
	m_GameManager->GetUdpNetwork()->SendAsync(pack);
}
