#pragma once

#include <UDPServer.hpp>
#include <Lobby.hpp>
#include <Managers/GameManager.hpp>
#include <Reloader/DirectoryWatcher.hpp>
#include <Parser/Parser.hpp>

namespace RType
{
	class GameInstance final : public IGameInstance
	{
	public:
		explicit GameInstance(const Pointer<Lobby> lobby);
		GameInstance(const GameInstance&) = delete;
		GameInstance(GameInstance&&) noexcept = default;
		~GameInstance() override = default;

	public:
		GameInstance& operator=(const GameInstance&) = delete;
		GameInstance& operator=(GameInstance&&) noexcept = default;

	public:
		bool StartGame() override;
		void SpawnMonster(const LevelInformation& info) const;
		size_t GetNbPlayerAlive(void) const;
		
	private:
		std::string m_ServerIp;
		std::uint32_t m_Port;
		UDPServer::UDPServerPtr m_UdpServer;
		Pointer<Lobby> m_Lobby;
		bool m_GameRunning = false;
		Unique<GameManager> m_GameManager;
		Unique<Parser> m_Parser;
		Unique<Loader> m_Loader;
		sf::Clock m_MonsterClock;
	};
}
