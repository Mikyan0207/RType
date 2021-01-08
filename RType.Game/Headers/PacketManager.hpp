#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <Network/Connection.hpp>
#include <Network/IPacketManager.hpp>
#include <Core.hpp>
#include <Managers/GameManager.hpp>

namespace RType
{
    class TCPClient;

    class PacketManager : public IPacketManager
    {
        public:
            PacketManager(Pointer<RType::TCPClient> server, Pointer<GameManager> gameManager);
            ~PacketManager() final = default;

        public:
            void Initialize() final;
            void CallbackHandler(const RType::RTypePack &p) final;
        
        public: // Callbacks
            void OnRoomCreated(const RType::RTypePack& p);
            void OnRoomJoined(const RType::RTypePack& p);
            void OnRoomLeft(const RType::RTypePack& p);
            void OnRoomPlayerJoined(const RType::RTypePack& p);
            void OnRoomPlayerLeft(const RType::RTypePack& p);
            void OnGameStart(const RType::RTypePack& p);
            void OnNotFoundReceived(const RType::RTypePack& p);

        private:
            Pointer<TCPClient> m_Client;
    		Pointer<GameManager> m_GameManager;
            std::unordered_map<RType::RTypePack::PackType, void (PacketManager::*)(const RType::RTypePack& p)> m_Callbacks;
    };
}