#include <Systems/LoadSystem.hpp>
#include <Entities/Entity.hpp>
#include <Components/Input.hpp>
#include <Components/Drawable.hpp>
#include <Components/Transform.hpp>
#include <filesystem>

LoadSystem::LoadSystem(const std::size_t& id, const Pointer<GameManager> gameManager)
{
	m_GameManager = gameManager;
	m_Id = "LoadSystem#" + std::to_string(id);

	m_ShootSizes.insert({"shoot_0.png", {18, 15}});
	m_ShootSizes.insert({"shoot_1.png", {18, 14}});
	m_ShootSizes.insert({"shoot_2.png", {33, 12}});
	m_ShootSizes.insert({"shoot_3.png", {49, 14}});
	m_ShootSizes.insert({"shoot_4.png", {65, 16}});
	m_ShootSizes.insert({"shoot_5.png", {81, 18}});
}

void LoadSystem::OnEntityCreated(const IEntity& e)
{
}

void LoadSystem::OnEntityDestroyed(const std::size_t& id)
{
}

void LoadSystem::Update(const double& deltaTime)
{
}

void LoadSystem::OnEvent(sf::Event& event)
{
}

const std::string& LoadSystem::GetId() const
{
	return m_Id;
}

void LoadSystem::OnPacket(const RType::RGamePack& pack)
{
	if (pack.code() != RType::RGamePack::LOAD)
		return;

	if (!pack.has_loadcontent())
	{
		std::cerr << "Received load packet without content." << std::endl;
		return;
	}

	const auto& content = pack.loadcontent();
	const auto path = std::filesystem::current_path().string();

	switch (content.type())
	{
		case RType::LoadPacket::PLAYER:
		{
			auto p = CreateUnique<Entity>(content.id());
			auto* pDrawable = new Drawable(
				Drawable::DrawableType::Player, "RType.Assets/Sprites/" + content.filename(),
				sf::IntRect(0, 0, 33, 18));
			pDrawable->SetAnimated(false, 5, 0.1);
			auto* pTransform = new Transform(
				sf::Vector2f(content.position().x(), content.position().y()),
				0,
				{ 2.0f, 2.0f }
			);
			auto* pInput = new Input(m_GameManager->GetKeys());

			p->AddComponent(pDrawable, Drawable::Id);
			p->AddComponent(pTransform, Transform::Id);
			p->AddComponent(pInput, Input::Id);
			m_GameManager->AddEntity(std::move(p));
		} break;
		case RType::LoadPacket::ALLY:
		{
			auto a = CreateUnique<Entity>(content.id());
			auto *ad = new Drawable(Drawable::DrawableType::Ally, "RType.Assets/Sprites/" + content.filename(), sf::IntRect(0, 0, 33, 18));
			auto *at = new Transform(
				sf::Vector2f(content.position().x(), content.position().y()),
				0,
				{2.0f, 2.0f});
			ad->SetAnimated(true, 5, 0.2);

			a->AddComponent(ad, Drawable::Id);
			a->AddComponent(at, Transform::Id);
			
			m_GameManager->AddEntity(std::move(a));
		} break;
		case RType::LoadPacket::ENEMY:
		{
			auto e = CreateUnique<Entity>(content.id());
			auto* ed = new Drawable(
				Drawable::DrawableType::Monster,
				"RType.Assets/Sprites/" + content.filename(),
				sf::IntRect(0, 0, content.size().x(), content.size().y())
			); // TODO: Change Sprite size.
			auto* et = new Transform(sf::Vector2f(content.position().x(), content.position().y()), 0, sf::Vector2f(2,2));

			et->SetScale({static_cast<float>(content.scale().x()), static_cast<float>(content.scale().y()) });
			ed->SetAnimated(true, content.animframeinfo().x(), content.animframeinfo().y());
			e->AddComponent(ed, Drawable::Id);
			e->AddComponent(et, Transform::Id);

			m_GameManager->AddEntity(std::move(e));
		} break;
		case RType::LoadPacket::ENEMY_BULLET:
		{
			auto e = CreateUnique<Entity>(content.id());
			auto* ed = new Drawable(
				Drawable::DrawableType::Monster,
				"RType.Assets/Sprites/" + content.filename(),
				sf::IntRect(0, 0, 16, 6)
			); // TODO: Change Sprite size.
			auto* et = new Transform(sf::Vector2f(static_cast<float>(content.position().x()), static_cast<float>(content.position().y())), 0, sf::Vector2f(2,2));

			ed->SetAnimated(true, 8, 0.5);
			et->SetVelocity(-0.2);

			e->AddComponent(ed, Drawable::Id);
			e->AddComponent(et, Transform::Id);

			m_GameManager->AddEntity(std::move(e));
		} break;
		case RType::LoadPacket::POWERUP:
		{
			// TODO: Add PowerUps.
		} break;
		case RType::LoadPacket::BASIC_SHOT:
		{
			auto e = CreateUnique<Entity>(content.id());
			auto dims = m_ShootSizes[content.filename()];
			auto* ed = new Drawable(
				Drawable::DrawableType::Object,
				"RType.Assets/Sprites/" + content.filename(), 
				sf::IntRect(0, 0, dims.x, dims.y)
			);
			auto* et = new Transform(sf::Vector2f(content.position().x(), content.position().y()), 0, {2.0f, 2.0f});
			ed->SetAnimated(false, ((content.filename() == "shoot_0.png") ? 3 : 2), 0);
			et->SetVelocity(2.0);
				
			e->AddComponent(ed, Drawable::Id);
			e->AddComponent(et, Transform::Id);

			m_GameManager->AddEntity(std::move(e));
			m_GameManager->GetSoundManager()->PlayMusic(SoundManager::SHOOT);
		} break;
		default:
		{
			// Ignore.
		} break;
	}
}
