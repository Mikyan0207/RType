#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <thread>
#include <string>
#include <Network/IPacketManager.hpp>
#include <Network/ITCPNetwork.hpp>
#include <Network/Connection.hpp>
#include <Lobby.hpp>

namespace RType
{
    class TCPServer : public ITCPNetwork
    {
    public:
        TCPServer(const std::int32_t& port);

    public:
        void Start() final;
        void Stop() final;
        void CheckClosedConnection();
        void WriteAsync(const std::string& ip, const RType::RTypePack& p);
        void StartGame() override {}
    	void CreateRoom(const std::uint32_t& maxPlayer) override {}
    	void JoinRoom(const std::string& roomId) override {}
    	void LeaveRoom(const std::string& roomId) override {}

    public:
        void AddLobby(Shared<Lobby> lobby);
        void RemoveLobby(const std::string &lobbyId);
        Shared<Lobby> GetLobby(const std::string& id);

    private:
        void StartAccept();
        void OnAccept(Connection::ConnectionPtr socket, const boost::system::error_code& error);

    public:
        [[nodiscard]] boost::asio::io_context& GetIoContext() { return m_IoContext; }
        [[nodiscard]] std::optional<std::string> GetServerIp() const;
        [[nodiscard]] std::optional<Connection::ConnectionPtr> GetConnectionFromIp(const std::string& ip);
        [[nodiscard]] Shared<RType::IUDPNetwork> GetUdpNetwork() const override { return {}; }

    private:
        std::vector<Shared<Lobby>> m_Rooms;
        boost::asio::io_context m_IoContext;
        boost::asio::ip::tcp::acceptor m_Acceptor;
        std::vector<Connection::ConnectionPtr> m_Connections;
        std::thread m_Thread;
        bool m_IsRunning;
        Unique<IPacketManager> m_PacketManager;
    };
}