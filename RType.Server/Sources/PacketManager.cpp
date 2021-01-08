#include <iostream>
#include <TCPServer.hpp>
#include <Models/RTypePack.pb.h>
#include <PacketManager.hpp>
#include <Logger.hpp>

namespace RType
{
    PacketManager::PacketManager(Pointer<RType::TCPServer> server)
    {
        m_Server = server;
    }

    /**
     * @brief Creates a @see std::map assigning @see RTypePack::PackType enums to functions
     */
    void PacketManager::Initialize()
    {
        m_Callbacks.insert(std::make_pair(RTypePack::CREATE_ROOM, &PacketManager::OnCreateRoom));
        m_Callbacks.insert(std::make_pair(RTypePack::JOIN_ROOM, &PacketManager::OnJoinRoom));
        m_Callbacks.insert(std::make_pair(RTypePack::LEAVE_ROOM, &PacketManager::OnLeaveRoom));
        m_Callbacks.insert(std::make_pair(RTypePack::START_GAME, &PacketManager::OnStartGame));
    }

    /**
     * @brief Calls the function corresponding to the @see RTypePack::PackType
     * stored in @see p and gives it p as parameter.
     * 
     * @param[in] p The packet containing the data to manage.
     * It can contain one and only one of the four following packets :
     * 
     */
    void PacketManager::CallbackHandler(const RType::RTypePack& p)
    {
        if (std::find_if(
            m_Callbacks.begin(),
            m_Callbacks.end(),
            [p](auto &e) -> bool {
            return e.first == p.code();
        }) == m_Callbacks.end())
        {
            std::cerr << "[CallbackHandler] - Unknown code." << std::endl;
            return;
        }
        (this->*m_Callbacks[p.code()])(p);
    }

    void PacketManager::OnCreateRoom(const RType::RTypePack& p)
    {
        auto connection = m_Server->GetConnectionFromIp(p.clientip());
        if (connection.has_value())
        {
            Logger::Log("Creating lobby...");
            auto lobby = Lobby::CreateLobby(p.clientip(), m_Server->GetServerIp().value(), m_Server->GetIoContext(), p.lobbycontent().maxplayer());
            Logger::Log("Lobby created.");
            auto wrapper = RType::RTypePack();
            auto content = new RType::LobbyPacket();

            wrapper.set_code(RTypePack::ROOM_CREATED);
            content->set_maxplayer(lobby->GetMaxPlayer());
            content->set_playerid(1);
            content->set_roomid(lobby->GetId());
            wrapper.set_allocated_lobbycontent(content);
            connection.value()->WriteAsync(wrapper);

            Logger::Log("\tRoom created with unique id=[" + lobby->GetId() + "] -> Owner : [" + p.clientip() + "].");
            m_Server->AddLobby(std::move(lobby));
        }
    }

    void PacketManager::OnJoinRoom(const RType::RTypePack& p)
    {
        Logger::Log("[OnJoinRoom]");
        auto lobby = m_Server->GetLobby(p.lobbycontent().roomid());
        auto playerConnection = m_Server->GetConnectionFromIp(p.clientip());

        if (!playerConnection.has_value())
        {
            Logger::Log("\t\033[1;31m[ERROR]\033[0m - Client connection [" + p.clientip() + "] not found for lobby with id=[" + lobby->GetId() + "].");
            return;
        }

        auto wrapper = RType::RTypePack();
        if (!lobby)
        { // Prepare packet when room does not exist
            Logger::Log("\t\033[1;33m[WARNING]\033[0m - Lobby [" + p.lobbycontent().roomid() + "] not found.");

            auto msg = new RType::ResponsePacket();

            wrapper.set_code(RTypePack::NOTFOUND);
            msg->set_code(ResponsePacket::BAD);
            msg->set_content("Could not find room with id=[" + p.lobbycontent().roomid() + "].");
            wrapper.set_allocated_responsecontent(msg);
        }
        else if (lobby->GetPlayerNb() == lobby->GetMaxPlayer())
        { // Prepare packet when room is full.
            Logger::Log("\t\033[1;33m[WARNING]\033[0m - Lobby [" + lobby->GetId() + \
            "] is full (" + std::to_string(lobby->GetPlayerNb()) + "/" + std::to_string(lobby->GetMaxPlayer()) + ")");

            auto content = new RType::LobbyPacket();

            wrapper.set_code(RTypePack::ROOM_IS_FULL);
            content->set_roomid(lobby->GetId());
            wrapper.set_allocated_lobbycontent(content);
        }
        else
        { // Prepare packet when everything is GUCCI.
            lobby->AddPlayer(p.clientip());
            auto players = lobby->GetPlayers();

            for (const auto& player : players)
            {
                auto pConn = m_Server->GetConnectionFromIp(player.first);
                if (pConn.has_value() && (player.first != p.clientip()))
                {
                    auto wrapper2 = RType::RTypePack();
                    auto content2 = new RType::LobbyPacket();
                    { // Set packet for each member of the lobby.
                        wrapper2.set_code(RTypePack::ROOM_PLAYER_JOINED);
                        content2->set_maxplayer(lobby->GetMaxPlayer());
                        content2->set_playerid(players.at(p.clientip()));
                        content2->set_roomid(lobby->GetId());
                        wrapper2.set_allocated_lobbycontent(content2);
                    }
                    pConn.value()->WriteAsync(wrapper2);
                }
            }

            { // Set packet for the one requesting to join the lobby
                auto content = new RType::LobbyPacket();

                wrapper.set_code(RTypePack::ROOM_JOINED);
                content->set_maxplayer(lobby->GetMaxPlayer());
                content->set_maxplayer(lobby->GetMaxPlayer());
                content->set_playerid(players.at(p.clientip()));
                content->set_roomid(lobby->GetId());
                wrapper.set_allocated_lobbycontent(content);
            }
            Logger::Log("\tRoom with id=[" + lobby->GetId() + "] -> player joined : " + p.clientip());
        }
        playerConnection.value()->WriteAsync(wrapper);
    }

    void PacketManager::OnLeaveRoom(const RType::RTypePack& p)
    {
        Logger::Log("[OnLeaveRoom]");
        auto lobby = m_Server->GetLobby(p.lobbycontent().roomid());
        auto playerConnection = m_Server->GetConnectionFromIp(p.clientip());

        if (!playerConnection.has_value())
        {
            Logger::Log("\t\033[1;31m[ERROR]\033[0m - Client connection not found for lobby with id=[" + lobby->GetId() + "].");
            return;
        }

        auto wrapper = RType::RTypePack();
        auto content = new RType::LobbyPacket();
        if (!lobby)
        { // Prepare packet when room does not exist
            Logger::Log("\t\033[1;33m[WARNING]\033[0m - Lobby [" + p.lobbycontent().roomid() + "] not found.");
            Logger::Log("\t\033[1;33m[WARNING]\033[0m - Faking player left.");

            wrapper.set_code(RTypePack::ROOM_LEFT);
            content->set_roomid(p.lobbycontent().roomid());
            wrapper.set_allocated_lobbycontent(content);
        }
        else
        {
            Logger::Log("\tRoom with id=[" + lobby->GetId()
                + "] -> player left : " + p.clientip() + ", players remaining : "
                + std::to_string(lobby->GetPlayerNb() - 1));

            auto &players = lobby->GetPlayers();
            for (const auto& player : players)
            {
                auto pConn = m_Server->GetConnectionFromIp(player.first);
                if (pConn.has_value() && (player.first != p.clientip()))
                {
                    auto wrapper2 = RType::RTypePack();
                    auto content2 = new RType::LobbyPacket();
                    { // Set packet for each member of lobby.
                        wrapper2.set_code(RTypePack::ROOM_PLAYER_LEFT);
                        content2->set_port(lobby->GetPlayerNb() - 1);
                        content2->set_maxplayer(lobby->GetMaxPlayer());
                        content2->set_playerid(players.at(p.clientip()));
                        content2->set_roomid(lobby->GetId());
                        wrapper2.set_allocated_lobbycontent(content2);
                    }
                    pConn.value()->WriteAsync(wrapper2);
                    Logger::Log("\tNotified [" + pConn.value()->GetSocket().remote_endpoint().address().to_string() + "] that player left.");
                }
            }
            { // Set packet for the one requesting to leave the lobby
                wrapper.set_code(RTypePack::ROOM_LEFT);
                content->set_maxplayer(lobby->GetMaxPlayer());
                content->set_roomid(lobby->GetId());
                wrapper.set_allocated_lobbycontent(content);
            }
            lobby->RemovePlayer(p.clientip());
            if (lobby->GetPlayerNb() == 0)
            { // Checking if there is any player left in the room.
                Logger::Log("\t\033[1;34m[INFO]\033[0m - Removing lobby with id=[" + lobby->GetId() + "]");
                m_Server->RemoveLobby(lobby->GetId());
            }
        }
        playerConnection.value()->WriteAsync(wrapper);
    }

    void PacketManager::OnStartGame(const RType::RTypePack& p)
    {
        Logger::Log("[OnStartGame]");
        auto lobby = m_Server->GetLobby(p.lobbycontent().roomid());

        if (!lobby)
        {
            auto sConn = m_Server->GetConnectionFromIp(p.clientip());

            if (sConn.has_value())
            {
                auto wrapper = RType::RTypePack();
                auto msg = new RType::ResponsePacket();

                wrapper.set_code(RTypePack::NOTFOUND);
                msg->set_code(ResponsePacket::BAD);
                msg->set_content("Could not find room with id=[" + p.lobbycontent().roomid() + "].");
                wrapper.set_allocated_responsecontent(msg);
                sConn.value()->WriteAsync(wrapper);
            }
            else
            {
                Logger::Log("\t\033[1;31m[ERROR]\033[0m - Client connection not found.");
            }
            return;
        }

        lobby->StartGame();
        Logger::Log("\tRoom with id=[" + lobby->GetId() + "] -> Game starting : Notifying players...");
        bool g = true;
        for (const auto& player : lobby->GetPlayers())
        {
            auto pConn = m_Server->GetConnectionFromIp(player.first);
            if (pConn.has_value())
            {
                auto wrapper = RType::RTypePack();
                auto content = new RType::LobbyPacket();
                { // Set packet for each member of lobby.
                    wrapper.set_code(RTypePack::START_GAME);
                    content->set_roomid(lobby->GetId());
                    content->set_udp_ip(lobby->GetServerIp());
                    content->set_port(lobby->GetUdpPort());
                    wrapper.set_allocated_lobbycontent(content);
                }
                pConn.value()->WriteAsync(wrapper);
                Logger::Log("\t\t\033[1;32m[OK]\033[0m - Player " + std::to_string(player.second) + " [" + player.first + "] notified.");
            }
            else
            {
                Logger::Log("\t\t\033[1;31m[ERROR]\033[0m - Player " + std::to_string(player.second) + "[" + player.first + "] not found.");
                g = false;
            }
        }
        Logger::Log(g ?
            "\t\033[1;32m[OK]\033[0m - All notifications were sent." :
            "\t\033[1;33m[WARNING]\033[0m - Some players were not notified."
        );
    }
}
