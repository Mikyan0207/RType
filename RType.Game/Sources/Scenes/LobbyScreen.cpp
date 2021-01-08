#include <Scenes/LobbyScreen.hpp>
#include <Scenes/MainScreen.hpp>
#include <Components/Button.hpp>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>
#include <Components/Parallax.hpp>
#include <Systems/ButtonSystem.hpp>
#include <filesystem>
#include <Logger.hpp>
#include <Systems/ParallaxSystem.hpp>
#include <Systems/DrawableSystem.hpp>
#include <Systems/TextSystem.hpp>

#include <TCPClient.hpp>

LobbyScreen::LobbyScreen(const std::size_t& id) : Scene(id)
{
}

void LobbyScreen::OnCreate(const Pointer<GameManager> gameManager)
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

 	auto buttonBackEntity = CreateUnique<Entity>();
	auto* buttonBack = new Button();
	buttonBack->Initialize(sf::Vector2f(50, 700), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Back", 40, sf::Color::White);
	buttonBack->SetCallback([=]()
	{
		gameManager->GetTcpNetwork()->LeaveRoom("");
		gameManager->SwitchScene(HOME_ID);
	});
	

	auto buttonStartEntity = CreateUnique<Entity>();
	auto* buttonStart = new Button();
	buttonStart->Initialize(sf::Vector2f(1250, 700), sf::Vector2f(300, 128), "RType.Assets/Sprites/button.png", font, "Play", 40, sf::Color::White);
	buttonStart->SetCallback([=]()
	{
		gameManager->GetTcpNetwork()->StartGame();
	});


	//// ----------------------------

	auto vssEnt1 = CreateUnique<Entity>(30);
	auto* vssDrawable1 = new Drawable(
		Drawable::DrawableType::Ally,
		"RType.Assets/Sprites/Player_0.png",
		sf::IntRect(0, 0, 33, 16)
	);
	vssDrawable1->SetAnimated(true, 5, 0.1);
	auto vssTransform1 = new Transform(sf::Vector2f(605, 225), 0, sf::Vector2f(2, 2));

	auto vssEnt2 = CreateUnique<Entity>(31);
	auto* vssDrawable2 = new Drawable(
		Drawable::DrawableType::Ally,
		"RType.Assets/Sprites/Player_1.png",
		sf::IntRect(0, 0, 33, 16)
	);
	vssDrawable2->SetAnimated(true, 5, 0.1);
	auto vssTransform2 = new Transform(sf::Vector2f(605, 325), 0, sf::Vector2f(2, 2));

	auto vssEnt3 = CreateUnique<Entity>(32);
	auto* vssDrawable3 = new Drawable(
		Drawable::DrawableType::Ally,
		"RType.Assets/Sprites/Player_2.png",
		sf::IntRect(0, 0, 33, 16)
	);
	vssDrawable3->SetAnimated(true, 5, 0.1);
	auto vssTransform3 = new Transform(sf::Vector2f(605, 425), 0, sf::Vector2f(2, 2));

	auto vssEnt4 = CreateUnique<Entity>(33);
	auto* vssDrawable4 = new Drawable(
		Drawable::DrawableType::Ally,
		"RType.Assets/Sprites/Player_3.png",
		sf::IntRect(0, 0, 33, 16)
	);
	vssDrawable4->SetAnimated(true, 5, 0.1);
	auto vssTransform4 = new Transform(sf::Vector2f(605, 525), 0, sf::Vector2f(2, 2));

	auto textPlayEntity1 = CreateUnique<Entity>(100);
	auto *textPlay1 = new Text();
	textPlay1->Initialize("- Empty", sf::Vector2f(700, 200), 60, sf::Color::White, font);

	auto textPlayEntity2 = CreateUnique<Entity>(101);
	auto *textPlay2 = new Text();
	textPlay2->Initialize("- Empty ", sf::Vector2f(700, 300), 60, sf::Color::White, font);
	
	auto textPlayEntity3 = CreateUnique<Entity>(102);
	auto *textPlay3 = new Text();
	textPlay3->Initialize("- Empty ", sf::Vector2f(700, 400), 60, sf::Color::White, font);
	
	auto textPlayEntity4 = CreateUnique<Entity>(103);
	auto *textPlay4 = new Text();
	textPlay4->Initialize("- Empty ", sf::Vector2f(700, 500), 60, sf::Color::White, font);


	/////-----------------------------


	auto textIdEntity = CreateUnique<Entity>(55);
	auto *textId = new Text();
	textId->Initialize("Id:XXXX", sf::Vector2f(50, 0), 60, sf::Color::White, font);

	auto textPlayerEntity = CreateUnique<Entity>(75);
	auto *textPlayer = new Text();
	textPlayer->Initialize("Player 1/4", sf::Vector2f(1250, 0), 60, sf::Color::White, font);

	parallaxEntity1->AddComponent(prlx1, Parallax::Id);
	parallaxEntity2->AddComponent(prlx2, Parallax::Id);
	parallaxEntity3->AddComponent(prlx3, Parallax::Id);
	buttonBackEntity->AddComponent(buttonBack, Button::Id);
	buttonStartEntity->AddComponent(buttonStart, Button::Id);
	textIdEntity->AddComponent(textId, Text::Id);
	vssEnt1->AddComponent(vssDrawable1, Drawable::Id);
	vssEnt1->AddComponent(vssTransform1, Transform::Id);
	vssEnt2->AddComponent(vssDrawable2, Drawable::Id);
	vssEnt2->AddComponent(vssTransform2, Transform::Id);
	vssEnt3->AddComponent(vssDrawable3, Drawable::Id);
	vssEnt3->AddComponent(vssTransform3, Transform::Id);
	vssEnt4->AddComponent(vssDrawable4, Drawable::Id);
	vssEnt4->AddComponent(vssTransform4, Transform::Id);
	textPlayEntity1->AddComponent(textPlay1, Text::Id);
	textPlayEntity2->AddComponent(textPlay2, Text::Id);
	textPlayEntity3->AddComponent(textPlay3, Text::Id);
	textPlayEntity4->AddComponent(textPlay4, Text::Id);
	textPlayerEntity->AddComponent(textPlayer, Text::Id);

	auto textSystem = CreateUnique<TextSystem>(1, gameManager->GetRenderWindow());
	auto buttonSystem = CreateUnique<ButtonSystem>(1, gameManager->GetRenderWindow());
	auto parallaxSystem = CreateUnique<ParallaxSystem>(1, gameManager->GetRenderWindow());
	auto drawableSystem = CreateUnique<DrawableSystem>(1, gameManager);

	AddEntity(std::move(parallaxEntity1));
	AddEntity(std::move(parallaxEntity2));
	AddEntity(std::move(parallaxEntity3));
	AddEntity(std::move(buttonBackEntity));
	AddEntity(std::move(buttonStartEntity));
	AddEntity(std::move(textIdEntity));
	AddEntity(std::move(vssEnt1));
	AddEntity(std::move(vssEnt2));
	AddEntity(std::move(vssEnt3));
	AddEntity(std::move(vssEnt4));
	AddEntity(std::move(textPlayEntity1));
	AddEntity(std::move(textPlayEntity2));
	AddEntity(std::move(textPlayEntity3));
	AddEntity(std::move(textPlayEntity4));
	AddEntity(std::move(textPlayerEntity));

	AddSystem(std::move(parallaxSystem));
	AddSystem(std::move(buttonSystem));
	AddSystem(std::move(textSystem));
	AddSystem(std::move(drawableSystem));
}