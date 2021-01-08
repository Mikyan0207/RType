#pragma once
#include <Network/IUDPNetwork.hpp>

#include <vector>

#include <boost/asio.hpp>

#include <Models/RGamePack.pb.h>
#include <Core.hpp>
#include <Systems/ISystem.hpp>

namespace RType
{
	class UDPServer final : public IUDPNetwork, public std::enable_shared_from_this<UDPServer>
	{
	public:
		typedef Shared<UDPServer> UDPServerPtr;

	public:
		UDPServer(std::string ipAddress, const std::uint32_t& port);
		UDPServer(const UDPServer&) = delete;
		UDPServer(UDPServer&&) noexcept = delete;
		~UDPServer() override;

	public:
		UDPServer& operator=(const UDPServer&) = delete;
		UDPServer& operator=(UDPServer&&) noexcept = delete;

	public:
		void Bind();
		void Start() override;
		void Stop() override;
		void SendAsync(RType::RGamePack& p) override;
		void SendAsync(RType::RGamePack& p, const std::size_t& id) override;
		void ReceiveAsync() override;
		void OnReceive(const boost::system::error_code& error, const std::size_t& bytes_transferred) override;

	public:
		void SetOnReceiveCallback(const std::function<void(const RType::RGamePack&)>& function);
		
	public:
		size_t GetPlayerNb() const { return m_EndpointMap.size(); }

    private:
        boost::asio::io_context m_IoContext;
        boost::asio::ip::udp::socket m_Socket;
        boost::asio::ip::udp::endpoint m_ServerEndpoint;
        boost::asio::ip::udp::endpoint m_Endpoint;

    private:
        std::thread m_Thread;
        const std::string m_IpAddress;
        std::map<std::uint32_t, boost::asio::ip::udp::endpoint> m_EndpointMap;
        const std::uint32_t m_Port;
        std::array<char, 100000> m_OutputBuffer = {0};
        char m_InputBuffer[100000] = {0};

    private: // Game
        std::function<void(const RType::RGamePack&)> m_OnReceiveCallback;
    };
}