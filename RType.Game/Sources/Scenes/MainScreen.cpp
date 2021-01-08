#include <Scenes/MainScreen.hpp>
#include <Components/Button.hpp>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>
#include <Components/Sprite.hpp>
#include <Components/Parallax.hpp>
#include <Scenes/LobbyScreen.hpp>
#include <Scenes/EndScreen.hpp>
#include <Scenes/JoinLobbyScreen.hpp>
#include <Scenes/OptionsScreen.hpp>
#include <Systems/ButtonSystem.hpp>
#include <filesystem>
#include <Logger.hpp>
#include <Systems/ParallaxSystem.hpp>
#include <Systems/TextInputSystem.hpp>

#include "TCPClient.hpp"
#include "Systems/TextSystem.hpp"

MainScreen::MainScreen(const std::size_t& id) : Scene(id)
{
}

void MainScreen::OnCreate(const Pointer<GameManager> gameManager)
{
	RType::Logger::Log("[Main Screen] - OnCreate");

	if (gameManager->GetSoundManager()->IsMusicPlaying(SoundManager::MusicType::GAME))
		gameManager->GetSoundManager()->StopMusic(SoundManager::MusicType::GAME);
	if (!gameManager->GetSoundManager()->IsMusicPlaying(SoundManager::MusicType::MENU))
		gameManager->GetSoundManager()->PlayMusic(SoundManager::MusicType::MENU);
	
	const auto dimension = gameManager->GetRenderWindow()->getSize();
	sf::Font font;

	font.loadFromFile("RType.Assets/Fonts/pixelfont.ttf");

	auto parallaxEntity1 = CreateUnique<Entity>();
	auto* prlx1 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner1.png",
		sf::IntRect(0, 0, 1600, 900),
		sf::IntRect(0, 0, 3200, 1600)
	);
	prlx1->SetSpeed(1);

	auto parallaxEntity2 = CreateUnique<Entity>();
	auto* prlx2 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner2.png",
		sf::IntRect(0, 0, 1600, 900),
		sf::IntRect(0, 0, 3200, 1600)
	);
	prlx2->SetSpeed(2);

	auto parallaxEntity3 = CreateUnique<Entity>();
	auto* prlx3 = new Parallax(
		Drawable::DrawableType::Object,
		"RType.Assets/Sprites/runner2_flipped.png",
		sf::IntRect(0, 0, 1600, 900),
		sf::IntRect(0, 0, 3200, 1600)
	);
	prlx3->SetSpeed(3);

	auto buttonPlayEntity = CreateUnique<Entity>();
	auto* buttonPlay = new Button();
	buttonPlay->Initialize(sf::Vector2f(650, 250), sf::Vector2f(300, 70), "RType.Assets/Sprites/button.png", font, "Create Lobby", 40, sf::Color::White);
	buttonPlay->SetCallback([=]()
	{
		gameManager->GetTcpNetwork()->CreateRoom(4);
	});

	auto joinLobbyEntity = CreateUnique<Entity>();
	auto* joinLobbyButton = new Button();
	joinLobbyButton->Initialize(sf::Vector2f(650, 400), sf::Vector2f(300, 70), "RType.Assets/Sprites/button.png", font, "Join Lobby", 40, sf::Color::White);
	joinLobbyButton->SetCallback([=]()
	{
		gameManager->SwitchScene(JLS_ID);
	});

	auto buttonOptionsEntity = CreateUnique<Entity>();
	auto* buttonOptions = new Button();
	buttonOptions->Initialize(sf::Vector2f(650, 550), sf::Vector2f(300, 70), "RType.Assets/Sprites/button.png", font, "Options", 40, sf::Color::White);
	buttonOptions->SetCallback([=]() { gameManager->SwitchScene(OPTIONS_ID); });

	auto buttonExitEntity = CreateUnique<Entity>();
	auto* buttonExit = new Button();
	buttonExit->Initialize(sf::Vector2f(650, 700), sf::Vector2f(300, 70), "RType.Assets/Sprites/button.png", font, "Exit", 40, sf::Color::White);
	buttonExit->SetCallback([=]() { gameManager->GetRenderWindow()->close(); });

	auto titleEntity = CreateUnique<Entity>();
	auto *titleText = new Text();
	titleText->Initialize("The incredible R-Type game", sf::Vector2f(475, 40), 60, sf::Color::White, font);

	parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);
	buttonPlayEntity->AddComponent(buttonPlay, Button::Id);
	joinLobbyEntity->AddComponent(joinLobbyButton, Button::Id);
	buttonOptionsEntity->AddComponent(buttonOptions, Button::Id);
	buttonExitEntity->AddComponent(buttonExit, Button::Id);
	titleEntity->AddComponent(titleText, Text::Id);

	auto buttonSystem = CreateUnique<ButtonSystem>(1, gameManager->GetRenderWindow());
	auto parallaxSystem = CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow());
	auto textSystem = CreateUnique<TextSystem>(1, gameManager->GetRenderWindow());

	AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(buttonPlayEntity));
	AddEntity(std::move(joinLobbyEntity));
	AddEntity(std::move(buttonOptionsEntity));
	AddEntity(std::move(buttonExitEntity));
	AddEntity(std::move(titleEntity));

	AddSystem(std::move(parallaxSystem));
	AddSystem(std::move(buttonSystem));
	AddSystem(std::move(textSystem));
}