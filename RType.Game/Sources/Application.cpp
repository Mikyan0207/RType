#include <Application.hpp>
#include <Components/Sprite.hpp>
#include <Scenes/MainScreen.hpp>
#include <Scenes/LobbyScreen.hpp>
#include <Scenes/JoinLobbyScreen.hpp>
#include <Scenes/GameScreen.hpp>
#include <Scenes/EndScreen.hpp>
#include <Scenes/OptionsScreen.hpp>
#include <iostream>

/// <summary>
/// Initialize a new Application
/// </summary>
Application::Application(const std::string& ip, const std::int32_t& port)
{
	std::string soundpath = "RType.Assets/Sound/";
	auto soundm = SoundManager();

	m_Window = CreateShared<sf::RenderWindow>(sf::VideoMode(1600, 900), "RType", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{ 0, 0, 4, 3, 0, sf::ContextSettings::Default, false });
	m_Window->setPosition(sf::Vector2i(0, 0));
	m_Window->setFramerateLimit(60);

	m_GameManager = CreateUnique<GameManager>(m_Window);
	m_Client = CreateShared<RType::TCPClient>(ip, port, m_GameManager.get());
	m_GameManager->SetTcpNetwork(m_Client);

	m_GameManager->AddScene(new MainScreen(HOME_ID));
	m_GameManager->AddScene(new LobbyScreen(LOBBY_ID));
	m_GameManager->AddScene(new OptionsScreen(OPTIONS_ID));
	m_GameManager->AddScene(new JoinLobbyScreen(JLS_ID));
	m_GameManager->AddScene(new GameScreen(GAME_ID));
	m_GameManager->AddScene(new EndScreen(END_ID));

	{ // Load Sounds
		soundm.LoadMusic(SoundManager::MusicType::MENU, soundpath + "Music_0.ogg");
		soundm.LoadMusic(SoundManager::MusicType::GAME, soundpath + "Music_1.ogg");
		soundm.LoadMusic(SoundManager::MusicType::SHOOT, soundpath + "Shoot_0.ogg");
		soundm.LoadMusic(SoundManager::MusicType::KILL, soundpath + "monster_hit.ogg");
		soundm.LoadMusic(SoundManager::MusicType::DEATH, soundpath + "player_hit.ogg");
	}
	m_GameManager->SetSoundManager(std::move(soundm));
	m_GameManager->SwitchScene(HOME_ID);
}

/// <summary>
/// Run application's main loop.
/// </summary>
void Application::Run() const
{
	sf::Event event = {};
	sf::Clock gameClock = {};
	const auto fps = 60.0;

	try
	{
		m_Client->Start();

		while (m_Window->isOpen())
		{
			while (m_Window->pollEvent(event))
			{
				// Close window: exit
				if (event.type == sf::Event::Closed)
					m_Window->close();

				m_GameManager->DispatchEvent(event);
			}

			m_Client->HandlePacket();

			if (gameClock.getElapsedTime().asMilliseconds() > (1000.0 / fps))
			{
				m_Window->clear(sf::Color::Black);
				m_GameManager->Update(gameClock.getElapsedTime().asMilliseconds());
				m_Window->display();
				gameClock.restart();
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
