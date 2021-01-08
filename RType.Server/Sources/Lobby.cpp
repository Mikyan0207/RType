#include <Lobby.hpp>
#include <GameInstance.hpp>
#include <Logger.hpp>

namespace RType
{
#pragma region
    std::vector<std::string> Lobby::TAKEN_IDS;
#pragma endregion
    Shared<Lobby> Lobby::CreateLobby(const std::string &creatorIp, const std::string& localIp, boost::asio::io_context& IoContext, const std::uint32_t& maxPlayer)
    {
        auto alpha_start = 'A';
        std::string uniqueId;

        for (int i = 0; i < 8; i++)
        {
            uniqueId += alpha_start + std::rand() % 26;
        }

        if (std::find(Lobby::TAKEN_IDS.begin(), Lobby::TAKEN_IDS.end(), uniqueId) != Lobby::TAKEN_IDS.end())
        {
            return CreateLobby(creatorIp, localIp, IoContext, maxPlayer);
        }

        auto lobby = CreateShared<Lobby>(uniqueId, localIp, IoContext, maxPlayer);
        lobby->AddPlayer(creatorIp);

        return lobby;
    }

    Lobby::Lobby(const std::string& id, const std::string& localIp, boost::asio::io_context& ioContext, const std::uint32_t& maxPlayer)
    : m_Id(id), m_LocalIp(localIp), m_MaxPlayer(maxPlayer), m_IoContext(ioContext)
    {
        static std::uint32_t UDP_PORT = 5000;

        m_UdpPort = UDP_PORT++;
        if (m_MaxPlayer == 0)
        {
            std::cerr << "There must be at least 1 player." << std::endl;
        }
        m_GameInstance = CreateUnique<GameInstance>(this);
    }

    Lobby::~Lobby()
    {
    }

    bool Lobby::AddPlayer(const std::string &ip)
    {
        if (m_Players.size() >= m_MaxPlayer)
        {
            return (false);
        }
        m_Players.insert(std::pair(ip, m_Players.size() + 1));
        return (true);
    }

    bool Lobby::RemovePlayer(const std::string &ip)
    {
        auto p = std::find_if(
            m_Players.begin(),
            m_Players.end(),
            [ip](auto &e) -> bool {
            return e.first == ip;
        });

        if (p == m_Players.end())
        {
            return (false);
        }
        m_Players.erase(p);
        return (true);
    }

    // Start UDP server and interpreter asynchronously
    void Lobby::StartGame()
    {
        m_GameResult = std::async(
            std::launch::async,
            [=]{ m_GameInstance->StartGame(); }
        );
    }
}