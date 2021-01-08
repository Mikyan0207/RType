#include <Scenes/JoinLobbyScreen.hpp>
#include <Scenes/MainScreen.hpp>
#include <Components/Button.hpp>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>
#include <Components/Sprite.hpp>
#include <Components/Parallax.hpp>
#include <Scenes/LobbyScreen.hpp>
#include <Scenes/OptionsScreen.hpp>
#include <Systems/ButtonSystem.hpp>
#include <filesystem>
#include <Logger.hpp>
#include <Systems/ParallaxSystem.hpp>
#include <Systems/TextInputSystem.hpp>
#include <Systems/TextSystem.hpp>

#include "TCPClient.hpp"

JoinLobbyScreen::JoinLobbyScreen(const std::size_t& id) : Scene(id)
{
	
}

void JoinLobbyScreen::OnCreate(const Pointer<GameManager> gameManager)
{
    RType::Logger::Log("[Main Screen] - OnCreate");

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

	auto titleEntity = CreateUnique<Entity>();
	auto *titleText = new Text();
	titleText->Initialize("Enter the XXXXXXXX key of your lobby", sf::Vector2f(440, 300), 60, sf::Color::White, font);

    auto buttonBackEntity = CreateUnique<Entity>();
	auto* buttonBack = new Button();
	buttonBack->Initialize(sf::Vector2f(50, 700), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Back", 40, sf::Color::White);
	buttonBack->SetCallback([=]() { gameManager->SwitchScene(HOME_ID); });

	auto textInputEntity = CreateUnique<Entity>();
	auto* textInput = new TextInput();
	textInput->Initialize(sf::Vector2f(250, 50), sf::Vector2f(700, 450), font);

	auto buttonJoinEntity = CreateUnique<Entity>();
	auto* buttonJoin = new Button();
	buttonJoin->Initialize(sf::Vector2f(1250, 700), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Join Lobby", 35, sf::Color::White);
	buttonJoin->SetCallback([=]()
		{
			const auto text = textInput->GetText();

			gameManager->GetTcpNetwork()->JoinRoom(text);
		});

	parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	buttonBackEntity->AddComponent(buttonBack, Button::Id);
	buttonJoinEntity->AddComponent(buttonJoin, Button::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);
	titleEntity->AddComponent(titleText, Text::Id);
	textInputEntity->AddComponent(textInput, TextInput::Id);

	auto textSystem = CreateUnique<TextSystem>(1, gameManager->GetRenderWindow());
	auto buttonSystem = CreateUnique<ButtonSystem>(1, gameManager->GetRenderWindow());
	auto textInputSystem = CreateUnique<TextInputSystem>(1, gameManager->GetRenderWindow());
	auto parallaxSystem = CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow());

	AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(buttonBackEntity));
	AddEntity(std::move(buttonJoinEntity));
	AddEntity(std::move(titleEntity));
	AddEntity(std::move(textInputEntity));

	AddSystem(std::move(parallaxSystem));
	AddSystem(std::move(buttonSystem));
	AddSystem(std::move(textSystem));
	AddSystem(std::move(textInputSystem));
}