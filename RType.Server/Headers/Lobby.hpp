#pragma once

#include <cstdint>
#include <map>
#include <algorithm>
#include <iostream>
#include <future>
#include <Core.hpp>
#include <boost/asio.hpp>
#include <IGameInstance.hpp>

namespace RType
{
    class Lobby
    {
    public:
        Lobby(const std::string& id, const std::string& localIp, boost::asio::io_context& ioContext, const std::uint32_t &maxPlayer = 4);
    	Lobby(const Lobby&) = delete;
    	Lobby(Lobby&&) noexcept = delete;
        ~Lobby();

    public:
		Lobby& operator=(const Lobby&) = delete;
		Lobby& operator=(Lobby&&) noexcept = delete;

    public:
        static Shared<Lobby> CreateLobby(const std::string &creatorIp, const std::string& localIp, boost::asio::io_context& IoContext, const std::uint32_t& maxPlayer = 4);

    public:
        bool AddPlayer(const std::string &ip);
        bool RemovePlayer(const std::string &ip);
        inline void SetUdpPort(const std::uint32_t& port) { m_UdpPort = port; }

    public:
        [[nodiscard]] std::string GetId() const { return (m_Id); }
        [[nodiscard]] std::size_t GetPlayerNb() const { return m_Players.size(); }
        [[nodiscard]] std::uint32_t GetMaxPlayer() const { return m_MaxPlayer; }
        [[nodiscard]] const boost::asio::io_context& GetIoContext() const { return m_IoContext; }
        [[nodiscard]] const std::string& GetServerIp() const { return (m_LocalIp); }
        [[nodiscard]] const std::uint32_t& GetUdpPort() const { return (m_UdpPort); }
        [[nodiscard]] const std::map <std::string, std::uint32_t>& GetPlayers() const { return m_Players; }

    public:
        void StartGame();

    private:
        const std::string m_LocalIp;
        std::uint32_t m_UdpPort;
        const std::string m_Id;
        boost::asio::io_context& m_IoContext;
        std::uint32_t m_MaxPlayer;
        std::map<std::string /* Player ip */, std::uint32_t /* Player id */> m_Players;
        Unique<IGameInstance> m_GameInstance;
        std::future<void> m_GameResult;

    public:
        static std::vector<std::string> TAKEN_IDS;
    };
}
