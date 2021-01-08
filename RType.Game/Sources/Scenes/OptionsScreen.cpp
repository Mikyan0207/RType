#include <Scenes/OptionsScreen.hpp>
#include <Scenes/MainScreen.hpp>
#include <filesystem>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>
#include <Components/DynamicButton.hpp>
#include <Components/Button.hpp>
#include <Components/Drawable.hpp>
#include <Components/Parallax.hpp>
#include <Helper.hpp>

#include <Systems/ParallaxSystem.hpp>
#include <Systems/DynamicButtonSystem.hpp>
#include <Systems/ButtonSystem.hpp>
#include <Systems/TextSystem.hpp>

OptionsScreen::OptionsScreen(const std::size_t& id) : Scene(id)
{
}

void OptionsScreen::OnCreate(const Pointer<GameManager> gameManager)
{
	auto keys = gameManager->GetKeys();
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

	parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);

#pragma region Up Key
	auto upKeyEntity = CreateUnique<Entity>();
	auto* upKeyText = new Text();
	auto* upDynamicButton = new DynamicButton();
	upDynamicButton->Initialize(sf::Vector2f(0, 100), sf::Vector2f(300, 60), "RType.Assets/Sprites/button.png", font, Helper::GetKeyAsString(keys[Inputs::Up]), 35, sf::Color::White);
	upDynamicButton->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	upDynamicButton->SetInput(Inputs::Up);

	upKeyText->Initialize("Up", sf::Vector2f(0, 50), 35, sf::Color::White, font);
	upKeyText->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	
	upKeyEntity->AddComponent(upDynamicButton, DynamicButton::Id);
	upKeyEntity->AddComponent(upKeyText, Text::Id);
#pragma endregion Up Key

#pragma region Down Key
	auto downKeyEntity = CreateUnique<Entity>();
	auto* downKeyText = new Text();
	auto* downDynamicButton = new DynamicButton();
	downDynamicButton->Initialize(sf::Vector2f(0, 200), sf::Vector2f(300, 60), "RType.Assets/Sprites/button.png", font, Helper::GetKeyAsString(keys[Inputs::Down]), 35, sf::Color::White);
	downDynamicButton->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	downDynamicButton->SetInput(Inputs::Down);

	downKeyText->Initialize("Down", sf::Vector2f(0, 150), 35, sf::Color::White, font);
	downKeyText->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());

	downKeyEntity->AddComponent(downDynamicButton, DynamicButton::Id);
	downKeyEntity->AddComponent(downKeyText, Text::Id);
#pragma endregion Down Key

#pragma region Left Key
	auto leftKeyEntity = CreateUnique<Entity>();
	auto* leftKeyText = new Text();
	auto* leftDynamicButton = new DynamicButton();
	leftDynamicButton->Initialize(sf::Vector2f(0, 300), sf::Vector2f(300, 60), "RType.Assets/Sprites/button.png", font, Helper::GetKeyAsString(keys[Inputs::Left]), 35, sf::Color::White);
	leftDynamicButton->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	leftDynamicButton->SetInput(Inputs::Left);

	leftKeyText->Initialize("Left", sf::Vector2f(0, 250), 35, sf::Color::White, font);
	leftKeyText->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());

	leftKeyEntity->AddComponent(leftDynamicButton, DynamicButton::Id);
	leftKeyEntity->AddComponent(leftKeyText, Text::Id);
#pragma endregion Left Key

#pragma region Right Key
	auto rightKeyEntity = CreateUnique<Entity>();
	auto* rightKeyText = new Text();
	auto* rightDynamicButton = new DynamicButton();
	rightDynamicButton->Initialize(sf::Vector2f(0, 400), sf::Vector2f(300, 60), "RType.Assets/Sprites/button.png", font, Helper::GetKeyAsString(keys[Inputs::Right]), 35, sf::Color::White);
	rightDynamicButton->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	rightDynamicButton->SetInput(Inputs::Right);

	rightKeyText->Initialize("Right", sf::Vector2f(0, 350), 35, sf::Color::White, font);
	rightKeyText->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());

	rightKeyEntity->AddComponent(rightDynamicButton, DynamicButton::Id);
	rightKeyEntity->AddComponent(rightKeyText, Text::Id);
#pragma endregion Right Key

#pragma region Shoot Key
	auto shootKeyEntity = CreateUnique<Entity>();
	auto* shootKeyText = new Text();
	auto* shootDynamicButton = new DynamicButton();
	shootDynamicButton->Initialize(sf::Vector2f(0, 500), sf::Vector2f(300, 60), "RType.Assets/Sprites/button.png", font, Helper::GetKeyAsString(keys[Inputs::Shoot]), 35, sf::Color::White);
	shootDynamicButton->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());
	shootDynamicButton->SetInput(Inputs::Shoot);

	shootKeyText->Initialize("Shoot", sf::Vector2f(0, 450), 35, sf::Color::White, font);
	shootKeyText->SetLayout(HorizontalLayout::Center, gameManager->GetRenderWindow());

	shootKeyEntity->AddComponent(shootDynamicButton, DynamicButton::Id);
	shootKeyEntity->AddComponent(shootKeyText, Text::Id);
#pragma endregion Shoot Key

 	auto buttonBackEntity = CreateUnique<Entity>();
	auto* buttonBack = new Button();
	buttonBack->Initialize(sf::Vector2f(350, 700), sf::Vector2f(300, 150), "RType.Assets/Sprites/button.png", font, "Back", 40, sf::Color::White);
	buttonBack->SetCallback([=]()
	{
		gameManager->SwitchScene(HOME_ID);
	});
	buttonBackEntity->AddComponent(buttonBack, Button::Id);

	auto textSystem = CreateUnique<TextSystem>(1, gameManager->GetRenderWindow());
	auto parallaxSystem = CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow());
	auto dbSystem = CreateUnique<DynamicButtonSystem>(1, gameManager);
	auto buttonSystem = CreateUnique<ButtonSystem>(1, gameManager->GetRenderWindow());

	AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(upKeyEntity));
	AddEntity(std::move(downKeyEntity));
	AddEntity(std::move(leftKeyEntity));
	AddEntity(std::move(rightKeyEntity));
	AddEntity(std::move(shootKeyEntity));
	AddEntity(std::move(buttonBackEntity));

	AddSystem(std::move(parallaxSystem));
	AddSystem(std::move(dbSystem));
	AddSystem(std::move(textSystem));
	AddSystem(std::move(buttonSystem));
}
