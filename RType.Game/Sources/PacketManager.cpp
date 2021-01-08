#include <iostream>
#include <TCPClient.hpp>
#include <PacketManager.hpp>
#include <Logger.hpp>
#include <Entities/Entity.hpp>
#include <Components/Text.hpp>


#include "Scenes/GameScreen.hpp"
#include "Scenes/LobbyScreen.hpp"

namespace RType
{
	PacketManager::PacketManager(Pointer<RType::TCPClient> client, Pointer<GameManager> gameManager)
	{
	    m_Client = client;
	    m_GameManager = gameManager;
	}

	/**
	 * @brief Creates a @see std::map assigning @see RTypePack::PackType enums to functions
	 */
	void PacketManager::Initialize()
	{
		m_Callbacks.insert(std::make_pair(RTypePack::ROOM_CREATED, &PacketManager::OnRoomCreated));
		m_Callbacks.insert(std::make_pair(RTypePack::ROOM_JOINED, &PacketManager::OnRoomJoined));
		m_Callbacks.insert(std::make_pair(RTypePack::ROOM_LEFT, &PacketManager::OnRoomLeft));
		m_Callbacks.insert(std::make_pair(RTypePack::ROOM_PLAYER_JOINED, &PacketManager::OnRoomPlayerJoined));
		m_Callbacks.insert(std::make_pair(RTypePack::ROOM_PLAYER_LEFT, &PacketManager::OnRoomPlayerLeft));
		m_Callbacks.insert(std::make_pair(RTypePack::START_GAME, &PacketManager::OnGameStart));
		m_Callbacks.insert(std::make_pair(RTypePack::NOTFOUND, &PacketManager::OnNotFoundReceived));
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
			// @throw
			return;
		}
		(this->*m_Callbacks[p.code()])(p);
	}

	void PacketManager::OnRoomCreated(const RType::RTypePack& p)
	{
		m_Client->SetLobbyInfo(true, p.lobbycontent().roomid());
		m_Client->SetIdInRoom(p.lobbycontent().playerid());
		Logger::Log("Room created with id=[" + p.lobbycontent().roomid() + "].");
		m_GameManager->SwitchScene(LOBBY_ID);

		auto frolianus = m_GameManager->GetIEntity(75)->AsEntity()->GetComponent<Text>();

		if (frolianus.has_value())
		{
			frolianus.value()->SetString("Player 1/" + std::to_string(p.lobbycontent().maxplayer()));
		}
		auto IdLobby = m_GameManager->GetIEntity(55)->AsEntity()->GetComponent<Text>();

		if (IdLobby.has_value())
		{
			IdLobby.value()->SetString("ID: " + m_Client->GetLobbyId());
		}
		auto pl1 = m_GameManager->GetIEntity(100)->AsEntity()->GetComponent<Text>();

		if (pl1.has_value())
		{
			pl1.value()->SetString("- Player " + std::to_string(p.lobbycontent().playerid()));
		}
	}

	void PacketManager::OnRoomJoined(const RType::RTypePack& p)
	{
		m_Client->SetLobbyInfo(true, p.lobbycontent().roomid());
		m_Client->SetIdInRoom(p.lobbycontent().playerid());
		Logger::Log("Room joined with id=[" + p.lobbycontent().roomid() + "].");
		m_GameManager->SwitchScene(LOBBY_ID);
		auto frolianus = m_GameManager->GetIEntity(75)->AsEntity()->GetComponent<Text>();
		auto IdLobby = m_GameManager->GetIEntity(55)->AsEntity()->GetComponent<Text>();

		if (IdLobby.has_value())
		{
			IdLobby.value()->SetString("ID: " + m_Client->GetLobbyId());
		}

		if (frolianus.has_value())
		{
			frolianus.value()->SetString("Player " + std::to_string(p.lobbycontent().playerid()) + "/" + std::to_string(p.lobbycontent().maxplayer()));
		}
		for (uint32_t i = 1; i <= p.lobbycontent().playerid(); ++i)
		{
			auto pl = m_GameManager->GetIEntity(99 + i)->AsEntity()->GetComponent<Text>();
			if (pl.has_value())
			{
				pl.value()->SetString("- Player " + std::to_string(i));
			}
		}
	}

	void PacketManager::OnRoomLeft(const RType::RTypePack& p)
	{
		m_Client->SetLobbyInfo(false);
		Logger::Log("Room left with id=[" + p.lobbycontent().roomid() + "].");
	}

	void PacketManager::OnRoomPlayerJoined(const RType::RTypePack& p)
	{
		Logger::Log("Room player joined with id=[" + p.lobbycontent().roomid() + "].");

		auto IdLobby = m_GameManager->GetIEntity(55)->AsEntity()->GetComponent<Text>();

		if (IdLobby.has_value())
		{
			IdLobby.value()->SetString("ID: " + m_Client->GetLobbyId());
		}
		auto frolianus = m_GameManager->GetIEntity(75)->AsEntity()->GetComponent<Text>();

		if (frolianus.has_value())
		{
			frolianus.value()->SetString("Player " + std::to_string(p.lobbycontent().playerid()) + "/" + std::to_string(p.lobbycontent().maxplayer()));
		}
		auto pl = m_GameManager->GetIEntity(99 + p.lobbycontent().playerid())->AsEntity()->GetComponent<Text>();

		if (pl.has_value())
		{
			pl.value()->SetString("- Player " + std::to_string(p.lobbycontent().playerid()));
		}
	}

	void PacketManager::OnRoomPlayerLeft(const RType::RTypePack& p)
	{
		Logger::Log("Room player left with id=[" + p.lobbycontent().roomid() + "].");

		auto playerNbEntity = m_GameManager->GetIEntity(75);
		if (playerNbEntity)
		{
			auto textComp = playerNbEntity->AsEntity()->GetComponent<Text>();
			if (textComp.has_value())
			{
				textComp.value()->SetString("Player " + std::to_string(p.lobbycontent().port()) + "/" + std::to_string(p.lobbycontent().maxplayer()));
			}
		}

		auto emplacementPlayer = m_GameManager->GetIEntity(99 + p.lobbycontent().playerid());
		if (emplacementPlayer)
		{
			auto pl = emplacementPlayer->AsEntity()->GetComponent<Text>();
			if (pl.has_value())
			{
				pl.value()->SetString("- Empty ");
			}
		}
	}

	void PacketManager::OnGameStart(const RType::RTypePack& p)
	{
		m_Client->StartUdp(p.lobbycontent().udp_ip(), p.lobbycontent().port(), m_GameManager);
		m_GameManager->SetCurrentUserId(p.lobbycontent().playerid());
		m_GameManager->SwitchScene(GAME_ID);
	}

	void PacketManager::OnNotFoundReceived(const RType::RTypePack& p)
	{
		std::cerr << ((p.responsecontent().code() == ResponsePacket::OK)
			? "\033[1;33m[WARNING]\033[0m"
			: "\033[1;31m[ERROR]\033[0m") << std::ends;
		Logger::Log(" - Message : \033[1m" + p.responsecontent().content() + "\033[0m");
	}
}
