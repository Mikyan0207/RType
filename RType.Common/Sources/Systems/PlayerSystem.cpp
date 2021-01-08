#include <Systems/PlayerSystem.hpp>
#include <Entities/Entity.hpp>
#include <Components/Transform.hpp>

#include "Logger.hpp"

PlayerSystem::PlayerSystem(const std::size_t& id, Pointer<GameManager> gameManager)
	: System<Drawable, Transform, Input>("PlayerSystem#" + std::to_string(id))
{
	m_KeyPressedMap.insert({ Inputs::Up, false });
	m_KeyPressedMap.insert({ Inputs::Down, false });
	m_KeyPressedMap.insert({ Inputs::Left, false });
	m_KeyPressedMap.insert({ Inputs::Right, false });
	m_KeyPressedMap.insert({ Inputs::Shoot, false });

	m_LoadAnimation = CreateUnique<Drawable>(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/load_player_shoot.png",
		sf::IntRect({0, 0, 32, 32})
	);
	m_LoadAnimation->SetAnimated(true, 8, 0.1);
	m_LoadAnimation->SetScale({ 1.5, 1.5 });

	m_GameManager = gameManager;
}

void PlayerSystem::Update(const double& deltaTime)
{
	for (auto && component : m_Components)
	{
		auto* drawable = std::get<Pointer<Drawable>>(component);
		auto* transform = std::get<Pointer<Transform>>(component);
		auto* input = std::get<Pointer<Input>>(component);

		if (m_KeyPressedMap[Inputs::Up])
		{
			auto wrapper = RType::RGamePack();
			auto* action = new RType::ActionPacket();

			wrapper.set_code(RType::RGamePack::ACTION);
			action->set_type(RType::ActionPacket::UP);
			action->set_id(static_cast<uint32_t>(drawable->GetEntityId()));
			wrapper.set_allocated_actioncontent(action);
			m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
			this->AnimateShip(AnimationType::UP, drawable, deltaTime);
		}

		if (m_KeyPressedMap[Inputs::Down])
		{
			auto wrapper = RType::RGamePack();
			auto* action = new RType::ActionPacket();

			wrapper.set_code(RType::RGamePack::ACTION);
			action->set_type(RType::ActionPacket::DOWN);
			action->set_id(static_cast<uint32_t>(drawable->GetEntityId()));
			wrapper.set_allocated_actioncontent(action);
			m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
			this->AnimateShip(AnimationType::DOWN, drawable, deltaTime);
		}

		if (m_KeyPressedMap[Inputs::Left])
		{
			auto wrapper = RType::RGamePack();
			auto* action = new RType::ActionPacket();

			wrapper.set_code(RType::RGamePack::ACTION);
			action->set_type(RType::ActionPacket::LEFT);
			action->set_id(static_cast<uint32_t>(drawable->GetEntityId()));
			wrapper.set_allocated_actioncontent(action);
			m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
		}

		if (m_KeyPressedMap[Inputs::Right])
		{
			auto wrapper = RType::RGamePack();
			auto* action = new RType::ActionPacket();

			wrapper.set_code(RType::RGamePack::ACTION);
			action->set_type(RType::ActionPacket::RIGHT);
			action->set_id(static_cast<uint32_t>(drawable->GetEntityId()));
			wrapper.set_allocated_actioncontent(action);
			m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
		}

		if (m_IsLoadingShoot)
		{
			m_ShootLevelInfo.first += deltaTime;

			m_ShootLevelInfo.second = static_cast<std::size_t>(m_ShootLevelInfo.first / 200.0);
			if (m_ShootLevelInfo.second > 5)
				m_ShootLevelInfo.second = 5;

			if (m_ShootLevelInfo.second != 0)
			{
				if (m_LoadAnimation->GetCurrentAnimationFrame() >= m_LoadAnimation->GetAnimationFrameNb() - 1)
				{
					m_LoadAnimation->SetAnimationFrame(3, 10.0);
				}
				else
				{
					m_LoadAnimation->Animate(deltaTime);
				}
				m_LoadAnimation->SetPosition({
					transform->GetPosition().x + (4 * transform->GetRect().width / 5),
					transform->GetPosition().y
				});
				m_GameManager->GetRenderWindow()->draw(m_LoadAnimation->GetSprite());
			}
		}

		if (m_KeyPressedMap[Inputs::Shoot])
		{
			auto wrapper = RType::RGamePack();
			auto* action = new RType::ActionPacket();

			wrapper.set_code(RType::RGamePack::ACTION);
			action->set_type(RType::ActionPacket::SHOOT);
			action->set_id(static_cast<uint32_t>(drawable->GetEntityId()));
			action->set_shootlevel(m_ShootLevelInfo.second);
			wrapper.set_allocated_actioncontent(action);
			m_GameManager->GetUdpNetwork()->SendAsync(wrapper);

			m_KeyPressedMap[Inputs::Shoot] = false;
			m_ShootLevelInfo = {0.0, 0};
			m_LoadAnimation->ResetAnimation();
		}

		if (!m_KeyPressedMap[Inputs::Up] && !m_KeyPressedMap[Inputs::Down])
		{
			this->AnimateShip(AnimationType::STABILIZE, drawable, deltaTime);
		}

		drawable->SetPosition(transform->GetPosition());
		drawable->SetRotation(transform->GetRotation());
		drawable->SetScale(transform->GetScale());
		transform->SetRect(drawable->GetGlobalBounds());

		m_GameManager->GetRenderWindow()->draw(drawable->GetSprite());
	}
}

void PlayerSystem::OnEvent(sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased)
		return;

	for (auto &&elem : m_Components)
	{
		auto* input = std::get<Pointer<Input>>(elem);

		if (event.key.code == input->GetKey(Inputs::Up))
		{
			m_KeyPressedMap[Inputs::Up] = event.type == sf::Event::KeyPressed;
		}
		else if (event.key.code == input->GetKey(Inputs::Down))
		{
			m_KeyPressedMap[Inputs::Down] = event.type == sf::Event::KeyPressed;
		}
		else if (event.key.code == input->GetKey(Inputs::Left))
		{
			m_KeyPressedMap[Inputs::Left] = event.type == sf::Event::KeyPressed;
		}
		else if (event.key.code == input->GetKey(Inputs::Right))
		{
			m_KeyPressedMap[Inputs::Right] = event.type == sf::Event::KeyPressed;
		}
		else if (event.key.code == input->GetKey(Inputs::Shoot))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				m_IsLoadingShoot = true;
			}
			else
			{
				m_IsLoadingShoot = false;
				m_KeyPressedMap[Inputs::Shoot] = true;
			}
		}
	}
}

void PlayerSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.code() == RType::RGamePack::POSITION)
	{
		if (!pack.has_positioncontent())
			return;

		const auto& positionContent = pack.positioncontent();
		for (int i = 0; i < positionContent.id_size(); ++i)
		{
			auto* entity = m_GameManager->GetIEntity(positionContent.id()[i]);

			if (entity)
			{
				auto transform = entity->AsEntity()->GetComponent<Transform>();

				if (transform.has_value())
				{
					transform.value()->SetPosition({
						static_cast<float>(positionContent.position()[i].x()),
						static_cast<float>(positionContent.position()[i].y())
					});
				}
			}
		}
	}
}

void PlayerSystem::AnimateShip(const AnimationType& aType, Pointer<Drawable>& drawable, const double& deltaTime)
{
	auto rect = drawable->GetSpriteRect();
	const auto currentFrame = drawable->GetCurrentAnimationFrame();

	if (aType == AnimationType::UP && currentFrame < 4)
	{
		drawable->SetAnimationFrame(currentFrame + 1, deltaTime);
	}
	else if (aType == AnimationType::DOWN && currentFrame > 0)
	{
		drawable->SetAnimationFrame(currentFrame - 1, deltaTime);
	}
	else if (aType == AnimationType::STABILIZE && currentFrame != 2)
	{
		drawable->SetAnimationFrame(currentFrame + ((currentFrame < 2) ? 1 : (-1)), deltaTime);
	}
}
