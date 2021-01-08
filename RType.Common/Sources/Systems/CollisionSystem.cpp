#include <Systems/CollisionSystem.hpp>
#include <Entities/Entity.hpp>

CollisionSystem::CollisionSystem(const std::size_t& id, const Pointer<GameManager> gameManager) : System<Drawable, Transform>("CollisionSystem#" + std::to_string(id))
{
	m_GameManager = gameManager;
}

void CollisionSystem::Update(const double& deltaTime)
{
	// ICI COLLISION.

	if (_playersTransform.empty())
		for (auto&& component : m_Components)
		{
			auto* transform = std::get<Pointer<Transform>>(component);
			if (transform->GetEntityId() < 4)
			{
				_playersTransform.push_back(transform);
			}
		}
	std::vector<Pointer<Transform>> boomVector;
	std::vector<Pointer<Transform>> MonsterVector;
	for (auto&& component : m_Components)
	{
		auto* transform = std::get<Pointer<Transform>>(component);
		if (transform->GetEntityId() >= 8000 && transform->GetEntityId() <= 9000)
		{
			for (auto && monster_transform: MonsterVector)
			{
				if (monster_transform->GetRect().intersects(transform->GetRect()))
				{
					this->sendCollision(transform->GetEntityId(), monster_transform->GetEntityId());
					m_GameManager->GetSoundManager()->PlayMusic(SoundManager::MusicType::KILL);
				}
			}
			boomVector.push_back(transform);
		}
		else if (transform->GetEntityId() > 4 && transform->GetEntityId() != 100000)
		{
			for (auto && player_transform: _playersTransform)
			{
				if (player_transform->GetRect().intersects(transform->GetRect()))
				{
					// collision
					this->sendCollision(transform->GetEntityId(), player_transform->GetEntityId());
				}
			}
			for (auto && boom_transform: boomVector)
			{
				if (boom_transform->GetRect().intersects(transform->GetRect()))
				{
					this->sendCollision(transform->GetEntityId(), boom_transform->GetEntityId());
					m_GameManager->GetSoundManager()->PlayMusic(SoundManager::MusicType::KILL);
				}
			}
			MonsterVector.push_back(transform);
		}
	}
}

void CollisionSystem::sendCollision(const std::uint32_t &fromId,const std::uint32_t &toId) 
{
	if (fromId < 4)
	{
		_playersTransform.erase(std::find_if(_playersTransform.begin(), _playersTransform.end(), [fromId](auto&& t) {return t->GetEntityId() == fromId; }));
	}
	else if (toId < 4)
	{
		_playersTransform.erase(std::find_if(_playersTransform.begin(), _playersTransform.end(), [toId](auto&& t) {return t->GetEntityId() == toId; }));
	}
	auto wrapper = RType::RGamePack();
	auto* collide = new RType::CollidePacket;
	collide->add_ids(fromId);
	collide->add_ids(toId);
	wrapper.set_allocated_collidepacket(collide);
	m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
}


void CollisionSystem::OnEvent(sf::Event& event)
{
	// Ignore.
}

void CollisionSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.has_collidepacket())
	{
		auto& collidePacket = pack.collidepacket();
		auto& ids = collidePacket.ids();
		
		auto wrapper = RType::RGamePack();
		wrapper.set_code(RType::RGamePack::DESTROY);
		auto* deletePacket = new RType::DestroyPacket();
		
		for (auto&& id : ids)
		{
			deletePacket->add_ids(id);
			m_GameManager->RemoveEntity(id);
			m_GameManager->RemoveMonsterId(id);
		}

		wrapper.set_allocated_destroycontent(deletePacket);
		m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
	}
}
