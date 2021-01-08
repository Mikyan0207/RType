#pragma once
#include <Network/IUDPNetwork.hpp>

#include <queue>
#include <optional>

#include <boost/asio.hpp>

#include <Models/RGamePack.pb.h>
#include <Core.hpp>

#include "Managers/GameManager.hpp"

namespace RType
{
	class UDPClient final: public IUDPNetwork
	{
		public:
			using UDPClientPtr = Shared<UDPClient>;
			UDPClient(const std::string& address, const std::int32_t& port, const std::uint32_t& pid, Pointer<GameManager> gameManager);
			~UDPClient() override;

		public:
			void Start() override;
			void Stop() override;
			void SendAsync(RGamePack& packet) override;
			void SendAsync(RType::RGamePack& p, const std::size_t& id) override {}
			void ReceiveAsync() override;
			void OnReceive(const boost::system::error_code& error, const std::size_t& bytes_transferred) final;
		
		public:
			std::optional<RType::RGamePack> GetPacket();

		private:
			std::uint32_t m_PlayerId;
			std::array<char, 100000> m_OutputBuffer = {0};
			char m_InputBuffer[100000] = {0};
			std::queue<RType::RGamePack> m_Packets;

		private:
			boost::asio::io_context m_IoContext;
			std::thread m_Thread;
			const std::string& _sAddress;
			const std::int32_t& _sPort;
			boost::asio::ip::udp::socket m_Socket;
			boost::asio::ip::udp::endpoint m_ServEndpoint;
			boost::asio::ip::udp::endpoint m_Endpoint;
			Pointer<GameManager> m_GameManager;
	};

}


