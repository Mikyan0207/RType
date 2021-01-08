#include <TCPClient.hpp>
#include <PacketManager.hpp>
#include <utility>
#include <Logger.hpp>

namespace RType
{
    TCPClient::TCPClient(std::string ip, const std::int32_t& port, Pointer<GameManager> gameManager) :
        m_IoContext(), m_ServerIp(std::move(ip)), m_Port(port), m_IsInLobby(false), m_CurrentLobbyId("")
    {
        m_Connection = Connection::Create(m_IoContext);
        m_PacketManager = CreateUnique<PacketManager>(this, gameManager);
        m_IsRunning = false;
        m_IdInRoom = 0;
        Logger::Log("Game client initialized.");
    }

    TCPClient::~TCPClient()
    {
    	m_IoContext.stop();

        if (m_Thread.joinable())
        {
            m_Thread.join();
        }
    }

    void TCPClient::Start()
    {
        m_PacketManager->Initialize();
        m_Connection->ConnectAsync(m_IoContext, m_ServerIp, std::to_string(m_Port));
        m_Thread = std::thread([ctx = &m_IoContext] { ctx->run(); });
    }

    void TCPClient::Stop()
    {

    }

    void TCPClient::WriteAsync(const RType::RTypePack& p)
    {
        if (m_Connection)
        {
            m_Connection->WriteAsync(p);
        }
    }

    void TCPClient::HandlePacket() const
    {
        auto p = m_Connection->GetPacket();
        if (p.has_value())
        {
            m_PacketManager->CallbackHandler(p.value());
        }
    }

    void TCPClient::CreateRoom(const std::uint32_t& maxPlayer)
    {
        if (maxPlayer > 4 || maxPlayer == 0)
        {
            Logger::Log("Player number must be between 1 and 4");
            return;
        }
        auto wrapper = RType::RTypePack();
        auto content = new RType::LobbyPacket();

        wrapper.set_code(RTypePack::CREATE_ROOM);
        content->set_maxplayer(4);
        wrapper.set_allocated_lobbycontent(content);
        this->WriteAsync(wrapper);
    }

    void TCPClient::JoinRoom(const std::string& roomId)
    {
        auto wrapper = RType::RTypePack();
        auto content = new RType::LobbyPacket();

        wrapper.set_code(RTypePack::JOIN_ROOM);
        content->set_roomid(roomId);
        wrapper.set_allocated_lobbycontent(content);
        this->WriteAsync(wrapper);
    }

    void TCPClient::LeaveRoom(const std::string& roomId)
    {
        auto wrapper = RType::RTypePack();
        auto content = new RType::LobbyPacket();

        wrapper.set_code(RTypePack::LEAVE_ROOM);
        content->set_roomid(m_CurrentLobbyId);
        wrapper.set_allocated_lobbycontent(content);
        this->WriteAsync(wrapper);
    }

    void TCPClient::StartGame()
    {
        if (!m_IsInLobby)
        {
            Logger::Log("[ERROR] - Not in a room. Cannot launch game.");
            return;
        }
        auto wrapper = RType::RTypePack();
        auto content = new RType::LobbyPacket();

        wrapper.set_code(RTypePack::START_GAME);
        content->set_roomid(m_CurrentLobbyId);
        wrapper.set_allocated_lobbycontent(content);
        this->WriteAsync(wrapper);
    }

	void TCPClient::StartUdp(const std::string& address, const std::int32_t& port, Pointer<GameManager> gameManager)
	{
		m_Cli = CreateShared<UDPClient>(address, port, m_IdInRoom, gameManager);
    	gameManager->SetUdpNetwork(m_Cli);
		m_Cli->Start();
	}

    Shared<RType::IUDPNetwork> TCPClient::GetUdpNetwork() const
    {
    	return m_Cli;
    }

    void TCPClient::SetLobbyInfo(const bool &isInLobby, const std::string &lobbyId)
    {
        m_IsInLobby = isInLobby;
        m_CurrentLobbyId = isInLobby ? lobbyId : "";
    }
}