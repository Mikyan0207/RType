#pragma once

#include <Core.hpp>
#include <RType.Common.hpp>
#include <Entities/IEntity.hpp>
#include <Systems/ISystem.hpp>
#include <Managers/Inputs.hpp>
#include <Network/ITCPNetwork.hpp>
#include <Models/RGamePack.pb.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Reloader/Loader.hpp>
#include <Managers/SoundManager.hpp>

class IScene;

class RTYPECOMMON_API GameManager
{
public:

	enum POWER_UPS {
		SPEED,
		SHIELD,
		ATTACK_SPEED
	};
	
	GameManager() = default;
	explicit GameManager(const Shared<sf::RenderWindow>& window);
	explicit GameManager(const Shared<RType::IUDPNetwork>& udpNetwork);
	explicit GameManager(const Shared<RType::ITCPNetwork>& tcpNetwork);
	explicit GameManager(const Shared<sf::RenderWindow>& window, const Shared<RType::ITCPNetwork>& tcpNetwork);
	explicit GameManager(const Shared<sf::RenderWindow>& window, const Shared<RType::IUDPNetwork>& udpNetwork);
    GameManager(const GameManager&) = delete;
    GameManager(GameManager&&) noexcept = delete;
    ~GameManager() = default;

public:
    GameManager& operator=(const GameManager&) = delete;
    GameManager& operator=(GameManager&&) noexcept = delete;

public:
    void Update(const double& delta, bool render = true);
	void DispatchEvent(sf::Event& event) const;
	void DispatchPacket(const RType::RGamePack& packet) const;
	void SwitchScene(const std::size_t& scene);
    void AddScene(IScene* scene);
	void AddEntity(Unique<IEntity>&& entity) const;
	void RemoveEntity(const std::size_t& id) const;
	void AddMonsterId(const std::size_t& id);
	void RemoveMonsterId(const std::size_t& id);
	
public:
	void SetKey(const Inputs& input, const sf::Keyboard::Key& key);
	void SetTcpNetwork(const Shared<RType::ITCPNetwork>& network);
	
	inline std::map<std::uint32_t, std::vector<POWER_UPS> > GetPowerUpsMap()const { return _power_up_map; };
	void SetUdpNetwork(const Shared<RType::IUDPNetwork>& network);
	void SetSoundManager(SoundManager&& soundmanager);
	void SetCurrentUserId(const std::size_t& id);
public:
	[[nodiscard]] Shared<sf::RenderWindow> GetRenderWindow() const;
	[[nodiscard]] Shared<SoundManager> GetSoundManager() const;
	[[nodiscard]] const std::unordered_map<Inputs, sf::Keyboard::Key>& GetKeys() const;
	[[nodiscard]] Pointer<IEntity> GetIEntity(const std::size_t& id) const;
	[[nodiscard]] Shared<RType::IUDPNetwork> GetUdpNetwork() const;
	[[nodiscard]] Shared<RType::ITCPNetwork> GetTcpNetwork() const;
	[[nodiscard]] const std::vector<std::size_t>& GetMonsterIds() const;
	[[nodiscard]] const std::size_t& GetCurrentUserId() const;
	[[nodiscard]] const std::vector<Unique<IEntity>>& GetEntities() const;

protected:
	[[nodiscard]] Pointer<IScene> GetScene(const std::size_t& id) const;

protected:
	std::map<std::uint32_t, std::vector<POWER_UPS> > _power_up_map;
	Shared<RType::IUDPNetwork> m_UdpNetwork;
	Shared<RType::ITCPNetwork> m_TcpNetwork;
	Shared<sf::RenderWindow> m_Window;
    Shared<SoundManager> m_SoundManager;

	std::size_t m_CurrentUserId = 0;
	std::size_t m_CurrentSceneId = 0;
	std::size_t m_PreviousSceneId = 0;
	std::unordered_map<std::size_t, IScene*> m_Scenes;
	std::unordered_map<Inputs, sf::Keyboard::Key> m_Keys;
	bool SceneChanged = false;
	std::vector<std::size_t> m_MonsterIds;
};
