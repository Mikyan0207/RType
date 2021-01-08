#include <GameInstance.hpp>
#include <Logger.hpp>

#include "ServerScene.hpp"
#include "Reloader/Interfaces/IMonster.hpp"
#include <Components/Monster.hpp>
#include <Components/Transform.hpp>
#include <Entities/Entity.hpp>

namespace RType
{
	GameInstance::GameInstance(const Pointer<Lobby> lobby) : m_Lobby(lobby)
	{
		m_Port = 0;
		m_Parser = CreateUnique<Parser>();
		m_Loader = CreateUnique<Loader>();
	}

	bool GameInstance::StartGame()
	{
		sf::Clock clock = {};
		const auto fps = 60.0;
		
		m_UdpServer = CreateShared<UDPServer>(m_Lobby->GetServerIp(), m_Lobby->GetUdpPort());
		m_GameManager = CreateUnique<GameManager>(m_UdpServer);
		
		m_GameManager->AddScene(new ServerScene(1, m_Lobby->GetPlayerNb()));
		m_UdpServer->SetOnReceiveCallback([this](const RType::RGamePack& p)
			{
				if (m_GameManager == nullptr)
				{
					Logger::Log("GameManager was null.");
				}
				else
				{
					m_GameManager->DispatchPacket(p);
				}
			});

		m_UdpServer->Start();
		m_Parser->Parse("RType.Assets/Levels/level1.txt");
		
		while (m_UdpServer->GetPlayerNb() < m_Lobby->GetPlayerNb())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		m_GameManager->SwitchScene(1);
		m_GameRunning = true;
		m_MonsterClock.restart();

		while (m_GameRunning)
		{
			const auto m = m_Parser->GetInformation(m_MonsterClock.getElapsedTime().asSeconds());
			if (m.has_value())
			{
				SpawnMonster(m.value());
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if (clock.getElapsedTime().asMilliseconds() > (1000.0 / fps))
			{
				m_GameManager->Update(clock.getElapsedTime().asMilliseconds(), false);
				clock.restart();
			}

			if ((m_Parser->IsEmpty() && m_GameManager->GetMonsterIds().empty()) || this->GetNbPlayerAlive() == 0)
			{
				std::cout << "Game [" << m_Lobby->GetId() << "] Ended" << std::endl;
				m_GameRunning = false;
			}
		}

		auto wrapper = RType::RGamePack();
		wrapper.set_code(RType::RGamePack::END_GAME);

		m_GameManager->GetUdpNetwork()->SendAsync(wrapper);
		
		return (true);
	}

	void GameInstance::SpawnMonster(const LevelInformation& info) const
	{
		try
		{
			m_Loader->Load(info.Monster);
			const auto monster = m_Loader->Instantiate<IMonster>("Instantiate");

			monster->SetPosition({ info.Position.x, info.Position.y });
			monster->SetPowerType(static_cast<IMonster::PowerType>(info.Power));

			auto monsterEntity = CreateUnique<Entity>(monster->GetId());
			auto* monsterComponent = CreatePointer<Monster>(monster);

			monsterEntity->AddComponent(monsterComponent, Monster::Id);
			m_GameManager->AddEntity(std::move(monsterEntity));
			m_GameManager->AddMonsterId(monster->GetId());

			auto wrapper = RGamePack();
			auto* load = new LoadPacket();

			wrapper.set_code(RGamePack::LOAD);
			load->set_id(static_cast<uint32_t>(monster->GetId()));
			load->set_filename(info.Monster + ".png");
			{ // Set Monster position
				auto* position = new Vector2();
				position->set_x(static_cast<double>(monster->GetPosition().first));
				position->set_y(static_cast<double>(monster->GetPosition().second));
				load->set_allocated_position(position);
			}
			{ // Set Monster scale
				auto* scale = new Vector2();
				scale->set_x(monster->GetScale().first);
				scale->set_y(monster->GetScale().second);
				load->set_allocated_scale(scale);
			}
			{ // Set Monster sprite size
				auto* spriteSize = new Vector2();
				spriteSize->set_x(monster->GetSize().first);
				spriteSize->set_y(monster->GetSize().second);
				load->set_allocated_size(spriteSize);
			}
			{ // Set Monster anim frame info
				auto* frameInfo = new Vector2(); // TODO set monster's frame info
				frameInfo->set_x(monster->GetAnimationFrameInfo().first);
				frameInfo->set_y(monster->GetAnimationFrameInfo().second);
				load->set_allocated_animframeinfo(frameInfo);
			}
			load->set_type(LoadPacket::ENEMY);
			wrapper.set_allocated_loadcontent(load);
			m_Loader->Close();
			m_UdpServer->SendAsync(wrapper);
		}
		catch (const RTypeException& e)
		{
			std::cerr << e << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	size_t GameInstance::GetNbPlayerAlive(void) const
	{
		size_t npa = 0;

		for (auto && elem : m_GameManager->GetEntities())
		{
			if (elem->GetId() <= 4)
				++npa;
		}
		return npa;
	}
}
