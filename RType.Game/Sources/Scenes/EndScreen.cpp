#include <Scenes/MainScreen.hpp>
#include <Components/Button.hpp>
#include <Scenes/LobbyScreen.hpp>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>
#include <Scenes/EndScreen.hpp>
#include <filesystem>
#include <Logger.hpp>
#include <Systems/DrawableSystem.hpp>
#include <Systems/ButtonSystem.hpp>
#include <Components/Transform.hpp>
#include "Systems/TextSystem.hpp"
#include <Systems/ParallaxSystem.hpp>
#include <Components/Parallax.hpp>

EndScreen::EndScreen(const std::size_t& id) : Scene(id)
{
}

void EndScreen::OnCreate(const Pointer<GameManager> gameManager)
{
	RType::Logger::Log("[End Screen] - OnCreate");
	
	const auto dimension = gameManager->GetRenderWindow()->getSize();
	sf::Font font;

	font.loadFromFile("RType.Assets/Fonts/pixelfont.ttf");

	auto titleEntity = CreateUnique<Entity>();
	auto *titleText = new Text();
	titleText->Initialize("END GAME", sf::Vector2f(520, 40), 150, sf::Color::White, font);

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

    auto ButtonMenuEnt = CreateUnique<Entity>(996);
	auto* ButtonMenu = new Button();
	ButtonMenu->Initialize(sf::Vector2f(300, 350), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Menu", 40, sf::Color::White);
	ButtonMenu->SetCallback([=]()
	{
		gameManager->SwitchScene(HOME_ID);
	});
    auto ButtonExitEnt = CreateUnique<Entity>(995);
	auto* ButtonExit = new Button();
	ButtonExit->Initialize(sf::Vector2f(1000, 350), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Exit", 40, sf::Color::White);
	ButtonExit->SetCallback([=]()
	{
		gameManager->GetRenderWindow()->close();
	});

    parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);
	titleEntity->AddComponent(titleText, Text::Id);
	ButtonMenuEnt->AddComponent(ButtonMenu, Button::Id);
	ButtonExitEnt->AddComponent(ButtonExit, Button::Id);

	auto buttonSystem = CreateUnique<ButtonSystem>(1, gameManager->GetRenderWindow());
	auto textSystem = CreateUnique<TextSystem>(1, gameManager->GetRenderWindow());
	auto parallaxSystem = CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow());

    AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(titleEntity));
    AddEntity(std::move(ButtonExitEnt));
	AddEntity(std::move(ButtonMenuEnt));

	AddSystem(std::move(parallaxSystem));
	AddSystem(std::move(textSystem));
	AddSystem(std::move(buttonSystem));

}