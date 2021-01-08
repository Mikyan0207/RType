#include <iostream>
#include <algorithm>
#include <Exceptions/RTypeException.hpp>
#include <Managers/GameManager.hpp>
#include <Scenes/IScene.hpp>
#include <Helper.hpp>

#include "Logger.hpp"

GameManager::GameManager(const Shared<sf::RenderWindow>& window)
{
	m_Keys[Inputs::Up] = sf::Keyboard::Z;
	m_Keys[Inputs::Left] = sf::Keyboard::Q;
	m_Keys[Inputs::Down] = sf::Keyboard::S;
	m_Keys[Inputs::Right] = sf::Keyboard::D;
	m_Keys[Inputs::Shoot] = sf::Keyboard::Space;

	m_TcpNetwork = nullptr;
	m_UdpNetwork = nullptr;
	m_Window = window;
}

GameManager::GameManager(const Shared<RType::IUDPNetwork>& udpNetwork)
{
	m_Keys[Inputs::Up] = sf::Keyboard::Z;
	m_Keys[Inputs::Left] = sf::Keyboard::Q;
	m_Keys[Inputs::Down] = sf::Keyboard::S;
	m_Keys[Inputs::Right] = sf::Keyboard::D;
	m_Keys[Inputs::Shoot] = sf::Keyboard::Space;

	m_TcpNetwork = nullptr;
	m_UdpNetwork =  udpNetwork;
	m_Window = nullptr;
}

GameManager::GameManager(const Shared<RType::ITCPNetwork>& tcpNetwork)
{
	m_Keys[Inputs::Up] = sf::Keyboard::Z;
	m_Keys[Inputs::Left] = sf::Keyboard::Q;
	m_Keys[Inputs::Down] = sf::Keyboard::S;
	m_Keys[Inputs::Right] = sf::Keyboard::D;
	m_Keys[Inputs::Shoot] = sf::Keyboard::Space;

	m_TcpNetwork = tcpNetwork;
	m_UdpNetwork = nullptr;
	m_Window = nullptr;
}

GameManager::GameManager(const Shared<sf::RenderWindow>& window, const Shared<RType::ITCPNetwork>& tcpNetwork)
{
	m_Keys[Inputs::Up] = sf::Keyboard::Z;
	m_Keys[Inputs::Left] = sf::Keyboard::Q;
	m_Keys[Inputs::Down] = sf::Keyboard::S;
	m_Keys[Inputs::Right] = sf::Keyboard::D;
	m_Keys[Inputs::Shoot] = sf::Keyboard::Space;

	m_TcpNetwork = tcpNetwork;
	m_UdpNetwork = nullptr;
	m_Window = window;
}

GameManager::GameManager(const Shared<sf::RenderWindow>& window, const Shared<RType::IUDPNetwork>& udpNetwork)
{
	m_Keys[Inputs::Up] = sf::Keyboard::Z;
	m_Keys[Inputs::Left] = sf::Keyboard::Q;
	m_Keys[Inputs::Down] = sf::Keyboard::S;
	m_Keys[Inputs::Right] = sf::Keyboard::D;
	m_Keys[Inputs::Shoot] = sf::Keyboard::Space;

	m_TcpNetwork = nullptr;
	m_UdpNetwork = udpNetwork;
	m_Window = window;
}

void GameManager::Update(const double& delta, bool render)
{
	if (SceneChanged)
	{
		SceneChanged = false;

		auto* scene = GetScene(m_PreviousSceneId);
		scene->OnDestroy();
	}
	
	auto* scene = GetScene(m_CurrentSceneId);

	scene->Update(delta);
}

void GameManager::DispatchEvent(sf::Event& event) const
{
	auto* scene = GetScene(m_CurrentSceneId);

	scene->DispatchEvent(event);
}

void GameManager::DispatchPacket(const RType::RGamePack& packet) const
{
	auto* scene = GetScene(m_CurrentSceneId);

	if (scene == nullptr)
	{
		RType::Logger::Log("Scene was null");
		return;
	}
	
	scene->DispatchPacket(packet);
}

void GameManager::SwitchScene(const std::size_t& scene)
{
	try
	{
		if (m_CurrentSceneId != 0)
		{
			m_PreviousSceneId = m_CurrentSceneId;
			SceneChanged = true;
		}

		m_CurrentSceneId = scene;
		auto* newScene = GetScene(m_CurrentSceneId);

		if (newScene != nullptr)
			newScene->OnCreate(this);
	}
	catch (const RTypeException& ex)
	{
		std::cerr << ex << std::endl;
	}
}

void GameManager::AddScene(IScene* scene)
{
	m_Scenes.insert(std::make_pair(scene->GetId(), scene));
}

void GameManager::AddEntity(Unique<IEntity>&& entity) const
{
	auto* scene = GetScene(m_CurrentSceneId);

	scene->AddEntity(std::move(entity));
}

void GameManager::RemoveEntity(const std::size_t& id) const
{
	auto* scene = GetScene(m_CurrentSceneId);

	scene->RemoveEntity(id);
}

void GameManager::AddMonsterId(const std::size_t& id)
{
	m_MonsterIds.emplace_back(id);
}

void GameManager::RemoveMonsterId(const std::size_t& id)
{
	const auto it = std::find_if(m_MonsterIds.begin(), m_MonsterIds.end(), [&id](const std::size_t& mId)
	{
		return mId == id;
	});

	if (it != m_MonsterIds.end())
		m_MonsterIds.erase(it);
}

Pointer<IEntity> GameManager::GetIEntity(const std::size_t& id) const
{
	auto* scene = GetScene(m_CurrentSceneId);

	return scene->GetEntity(id);
}

void GameManager::SetKey(const Inputs& input, const sf::Keyboard::Key& key)
{
	m_Keys[input] = key;

	std::cout << Helper::GetKeyAsString(m_Keys[input]) << std::endl;
}

void GameManager::SetTcpNetwork(const Shared<RType::ITCPNetwork>& network)
{
	m_TcpNetwork = network;
}

void GameManager::SetUdpNetwork(const Shared<RType::IUDPNetwork>& network)
{
	m_UdpNetwork = network;
}

void GameManager::SetSoundManager(SoundManager&& soundmanager)
{
	m_SoundManager = CreateShared<SoundManager>(std::move(soundmanager));
}

void GameManager::SetCurrentUserId(const std::size_t& id)
{
	m_CurrentUserId = id;
}

const std::size_t& GameManager::GetCurrentUserId() const
{
	return m_CurrentUserId;
}

const std::vector<Unique<IEntity>>& GameManager::GetEntities() const
{
	auto* scene = this->GetScene(m_CurrentSceneId);

	return (scene->GetEntities());
}

Shared<sf::RenderWindow> GameManager::GetRenderWindow() const
{
	return m_Window;
}

Shared<SoundManager> GameManager::GetSoundManager() const
{
	return m_SoundManager;
}

const std::unordered_map<Inputs, sf::Keyboard::Key>& GameManager::GetKeys() const
{
	return m_Keys;
}

Pointer<IScene> GameManager::GetScene(const std::size_t& id) const
{
	const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&id](const std::pair<std::size_t, IScene*>& scene) -> bool
		{
			return scene.first == id;
		});

	if (it == m_Scenes.end())
		return nullptr;

	return it->second;
}

Shared<RType::IUDPNetwork> GameManager::GetUdpNetwork() const
{
	return m_UdpNetwork;
}

Shared<RType::ITCPNetwork> GameManager::GetTcpNetwork() const
{
	return m_TcpNetwork;
}

const std::vector<std::size_t>& GameManager::GetMonsterIds() const
{
	return m_MonsterIds;
}
