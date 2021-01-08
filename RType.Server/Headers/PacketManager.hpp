#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <Network/Connection.hpp>
#include <Network/IPacketManager.hpp>
#include <Core.hpp>

namespace RType
{
    class TCPServer;

    class PacketManager : public IPacketManager
    {
        public:
            PacketManager(Pointer<RType::TCPServer> server);
            ~PacketManager() final = default;

        public:
            void Initialize() final;
            void CallbackHandler(const RType::RTypePack &p) final;

        public: // Callbacks
            void OnCreateRoom(const RType::RTypePack& p);
            void OnJoinRoom(const RType::RTypePack& p);
            void OnLeaveRoom(const RType::RTypePack& p);
            void OnStartGame(const RType::RTypePack& p);

        private:
            Pointer<TCPServer> m_Server;
            std::unordered_map<RType::RTypePack::PackType, void (PacketManager::*)(const RType::RTypePack& p)> m_Callbacks;
    };
}