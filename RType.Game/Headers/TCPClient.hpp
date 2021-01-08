#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <Network/IPacketManager.hpp>
#include <Network/ITCPNetwork.hpp>
#include <Network/Connection.hpp>
#include <UDPClient.hpp>
#include <Core.hpp>

class GameManager;

namespace RType
{
	class TCPClient final : public ITCPNetwork
	{
	public:
		TCPClient(std::string ip, const std::int32_t& port, Pointer<GameManager> gameManager);
		TCPClient(const TCPClient&) = delete;
		TCPClient(TCPClient&&) noexcept = delete;
		~TCPClient() override;

	public:
		TCPClient& operator=(const TCPClient&) = delete;
		TCPClient& operator=(TCPClient&&) noexcept = delete;
		
	
	public:
		void Start() override;
		void Stop() override;
		void WriteAsync(const RType::RTypePack& p);
		void HandlePacket() const;

	public:
		void CreateRoom(const std::uint32_t& maxPlayer) override;
		void JoinRoom(const std::string& roomId) override;
		void LeaveRoom(const std::string& roomId) override;
		void StartGame() override;

	public:
		void SetLobbyInfo(const bool &isInLobby, const std::string &lobbyId = "");
		void SetIdInRoom(const std::uint32_t id) { m_IdInRoom = id; }

	public:
		std::string GetLobbyId() {return m_CurrentLobbyId;}
	public:
		void StartUdp(const std::string& address, const std::int32_t& port, Pointer<GameManager> gameManager);

	public:
		[[nodiscard]] Shared<RType::IUDPNetwork> GetUdpNetwork() const override;

	private:
		boost::asio::io_context m_IoContext;
		Connection::ConnectionPtr m_Connection;
		Unique<IPacketManager> m_PacketManager;

	private:
		std::string m_ServerIp;
		std::int32_t m_Port;
		std::thread m_Thread;
		bool m_IsRunning;
		bool m_IsInLobby;
		Shared<RType::IUDPNetwork> m_Cli;
		std::uint32_t m_IdInRoom;
		std::string m_CurrentLobbyId;
	};
}