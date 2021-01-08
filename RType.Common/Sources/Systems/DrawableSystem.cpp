#include <Systems/DrawableSystem.hpp>
#include <Entities/Entity.hpp>

#include "Logger.hpp"

DrawableSystem::DrawableSystem(const std::size_t& id, const Pointer<GameManager> gameManager) : System<Drawable, Transform>("DrawableSystem#" + std::to_string(id))
{
	m_GameManager = gameManager;
}

void DrawableSystem::Update(const double& deltaTime)
{
	for (auto && component : m_Components)
	{
		auto* drawable = std::get<Pointer<Drawable>>(component);
		auto* transform = std::get<Pointer<Transform>>(component);

		//if (drawable->GetEntityId() == m_GameManager->GetCurrentUserId())
		//{
		//	std::cout << "Current user id = " << m_GameManager->GetCurrentUserId() << std::endl;
		//	std::cout << "Not animating bc id = " << drawable->GetEntityId() << std::endl;
		//	continue;
		//}

		auto pos = transform->GetPosition();

		transform->SetPosition({
			pos.x + static_cast<float>((transform->GetVelocity()) * deltaTime),
			pos.y
		});

		drawable->SetPosition(transform->GetPosition());
		drawable->SetRotation(transform->GetRotation());
		drawable->SetScale(transform->GetScale());
		drawable->Animate(deltaTime);

		transform->SetRect(drawable->GetGlobalBounds());
		if (transform->GetEntityId() >= 8000 &&
			drawable->GetCurrentAnimationFrame() < drawable->GetAnimationFrameNb())
		{
			drawable->SetAnimationFrame(drawable->GetCurrentAnimationFrame() + 1, deltaTime);
		}
		
		m_GameManager->GetRenderWindow()->draw(drawable->GetSprite());
	}
}

void DrawableSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.code() == RType::RGamePack::POSITION)
	{
		if (!pack.has_positioncontent())
			return;

		const auto& positionContent = pack.positioncontent();

		for (auto i = 0; i < positionContent.id_size(); ++i)
		{
			if (positionContent.id()[i] == m_GameManager->GetCurrentUserId())
				continue;

			auto* entity = m_GameManager->GetIEntity(positionContent.id()[i]);

			if (!entity)
				continue;

			auto component = entity->AsEntity()->GetComponent<Transform>();
			if (component.has_value())
			{
				if (!positionContent.velocity_size())
				{
					component.value()->SetPosition({
						static_cast<float>(positionContent.position()[i].x()),
						static_cast<float>(positionContent.position()[i].y())
					});
				}
				else
				{
					component.value()->SetVelocity(positionContent.velocity()[i]);
				}
			}
		}
	}
	else if (pack.code() == RType::RGamePack::DESTROY)
	{
		for (auto && id : pack.destroycontent().ids())
		{
			std::cout << "Destroy Entity with Id: " << id << std::endl;
			m_GameManager->RemoveEntity(id);
		}
	}
}
