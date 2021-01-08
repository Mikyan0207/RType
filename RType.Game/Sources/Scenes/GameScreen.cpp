#include <Scenes/GameScreen.hpp>
#include <Systems/PlayerSystem.hpp>
#include <Systems/DrawableSystem.hpp>
#include <Systems/ParallaxSystem.hpp>
#include <Systems/LoadSystem.hpp>
#include <Entities/Entity.hpp>

#include <filesystem>
#include <Logger.hpp>

#include "Systems/CollisionSystem.hpp"

GameScreen::GameScreen(const std::size_t& id) : Scene(id)
{
}

void GameScreen::OnCreate(Pointer<GameManager> gameManager)
{
	RType::Logger::Log("[Game Screen] - OnCreate");
	AddSystem(CreateUnique<LoadSystem>(1, gameManager));
	AddSystem(CreateUnique<CollisionSystem>(1, gameManager));

	gameManager->GetSoundManager()->StopMusic(SoundManager::MusicType::MENU);
	gameManager->GetSoundManager()->PlayMusic(SoundManager::MusicType::GAME, 10.0f);

	const auto dimension = gameManager->GetRenderWindow()->getSize();

	auto parallaxEntity1 = CreateUnique<Entity>(100000);
	auto* prlx1 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner1.png",
		sf::IntRect(0, 0, dimension.x, dimension.y)
	);
	prlx1->SetSpeed(1);

	auto parallaxEntity2 = CreateUnique<Entity>(100000);
	auto* prlx2 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner2.png",
		sf::IntRect(0, 0, dimension.x, dimension.y)
	);
	prlx2->SetSpeed(2);

	auto parallaxEntity3 = CreateUnique<Entity>(100000);
	auto* prlx3 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner2_flipped.png",
		sf::IntRect(0, 0, dimension.x, dimension.y)
	);
	prlx3->SetSpeed(3);

	auto parallaxEntity4 = CreateUnique<Entity>(100000);
	auto* prlx4 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/WallUp.png",
		sf::IntRect(0, 0, dimension.x, 35)
	);
	prlx4->SetSpeed(4);

	auto parallaxEntity5 = CreateUnique<Entity>(100000);
	auto* prlx5 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/WallDown.png",
		sf::IntRect(0, 0, dimension.x, 35)
	);
	prlx5->SetPosition({0.0, static_cast<float>(dimension.y) - 35.0f});
	prlx5->SetSpeed(4);

	parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);
	parallaxEntity4->AddComponent(prlx4, Parallax::Id);
	parallaxEntity5->AddComponent(prlx5, Parallax::Id);

	AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(parallaxEntity4));
	AddEntity(std::move(parallaxEntity5));

	AddSystem(CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow()));
	AddSystem(CreateUnique<DrawableSystem>(1, gameManager));
	AddSystem(CreateUnique<PlayerSystem>(1, gameManager));
}