#include <TCPServer.hpp>
#include <iostream>
#include <PacketManager.hpp>
#include <algorithm>
#include <Logger.hpp>

namespace RType
{
    TCPServer::TCPServer(const std::int32_t& port) :
        m_Acceptor(m_IoContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), static_cast<unsigned short>(port)))
    {
        m_Connections = std::vector<Connection::ConnectionPtr>();
        m_PacketManager = CreateUnique<PacketManager>(this);
        m_IsRunning = false;
    }

    void TCPServer::Start()
    {
        m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_PacketManager->Initialize();

        this->StartAccept();
        m_Thread = std::thread([this]() { m_IoContext.run(); });
        m_IsRunning = true;

        while (m_IsRunning)
        {
            CheckClosedConnection();

            for (auto& conn : m_Connections)
            {
                if (!conn->IsOpen())
                    continue;
                
                auto p = conn->GetPacket();
                if (p.has_value())
                {
                    p.value().set_clientip(conn->GetSocket().remote_endpoint().address().to_string());
                    m_PacketManager->CallbackHandler(p.value());
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        google::protobuf::ShutdownProtobufLibrary();
    }

    void TCPServer::Stop()
    {
        m_IsRunning = false;
    }

    void TCPServer::CheckClosedConnection()
    {
        auto it = std::find_if(m_Connections.begin(), m_Connections.end(), [](const Connection::ConnectionPtr& p) {
            return p->IsOpen() == false;
        });

        // (」°ロ°)」
        while (it != m_Connections.end())
        {
            // @TODO remove player from his room.
            m_Connections.erase(it);

            it = std::find_if(m_Connections.begin(), m_Connections.end(), [](const Connection::ConnectionPtr& p) {
                return p->IsOpen() == false;
            });
        }
    }

    void TCPServer::WriteAsync(const std::string& ip, const RType::RTypePack& p)
    {
        auto conn = GetConnectionFromIp(ip);

        if (!conn.has_value()) {
            Logger::Log("Connection Socket not found. WriteAsync failed.");
            return;
        }

        conn.value()->WriteAsync(p);
    }

    void TCPServer::StartAccept()
    {
	    auto newConnection = Connection::Create(m_IoContext);

        m_Acceptor.async_accept(newConnection->GetSocket(),
            [=] (const boost::system::error_code& error) { OnAccept(newConnection, error); });
    }

    void TCPServer::OnAccept(Connection::ConnectionPtr socket, const boost::system::error_code& error)
    {
        if (error)
        {
            std::cerr << "[OnAccept] " << error.message() << std::endl;
        }
        else
        {
            std::cout << "[OnAccept] Client Connected to Server. [" << socket->GetSocket().remote_endpoint().address() << "]" << std::endl;
            socket->Start();
            socket->ReadAsync();
            m_Connections.push_back(socket);
            StartAccept();
        }
    }

    void TCPServer::AddLobby(Shared<Lobby> lobby)
    {
        m_Rooms.push_back(lobby);
    }

    void TCPServer::RemoveLobby(const std::string& id)
    {
        const auto it = std::find_if(
            m_Rooms.begin(),
            m_Rooms.end(),
            [&id](const Shared<Lobby> &lobby) {
                return id == lobby->GetId();
            }
        );

        if (it == m_Rooms.end())
            return;
        m_Rooms.erase(it);
    }

    Shared<Lobby> TCPServer::GetLobby(const std::string& id)
    {
        auto it = std::find_if(
            m_Rooms.begin(),
            m_Rooms.end(),
            [=](const Shared<Lobby> &l)
            {
                return l->GetId() == id;
            });

        if (it != m_Rooms.end())
            return *it;
        return nullptr;
    }

    std::optional<std::string> TCPServer::GetServerIp() const
    {
        if (!m_Connections.empty())
            return m_Connections.at(0)->GetSocket().local_endpoint().address().to_string();
        return {};
    }

    std::optional<Connection::ConnectionPtr> TCPServer::GetConnectionFromIp(const std::string& ip)
    {
        const auto con = std::find_if(
            m_Connections.begin(),
            m_Connections.end(),
            [&ip](const Connection::ConnectionPtr& conPtr) {
                return ip == conPtr->GetSocket().remote_endpoint().address().to_string();
            }
        );

        if (con == m_Connections.end())
            return {};

        return *con;
    }
}
