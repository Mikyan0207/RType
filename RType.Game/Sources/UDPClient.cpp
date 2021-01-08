#include <UDPClient.hpp>
#include <Logger.hpp>

#include <Scenes/EndScreen.hpp>

using boost::asio::ip::udp;

namespace RType
{
	UDPClient::UDPClient(const std::string& address, const std::int32_t& port, const std::uint32_t& pid, Pointer<GameManager> gameManager)
		: m_PlayerId(pid), m_IoContext(), _sAddress(address), _sPort(port), m_Socket(m_IoContext)
	{
		udp::resolver resolver(m_IoContext);
		udp::resolver::query query(udp::v4(), _sAddress, std::to_string(_sPort));
		udp::resolver::iterator iter = resolver.resolve(query);

		m_GameManager = gameManager;
		m_ServEndpoint = *iter;
		m_Socket.open(udp::v4());
	}

	UDPClient::~UDPClient()
	{
		this->Stop();
	}

	void UDPClient::SendAsync(RGamePack &p)
	{
		try
		{
			p.set_playerid(m_PlayerId);
			if (!p.SerializeToArray(m_InputBuffer, p.ByteSizeLong()))
			{
				std::cerr << "[Send] - Failed to Serialize" << std::endl;
				return;
			}
			m_Socket.send_to(boost::asio::buffer(m_InputBuffer, p.ByteSizeLong()), m_ServEndpoint);
			// Logger::Log("[UDP - Send] " + std::to_string(p.ByteSizeLong()) + " bytes transferred.");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void UDPClient::ReceiveAsync()
	{
		try
		{
			m_Socket.async_receive_from(
				boost::asio::buffer(m_OutputBuffer), m_Endpoint,
				[this](const boost::system::error_code& error, const std::size_t& bytes_transferred)
				{
					this->OnReceive(error, bytes_transferred);
				});
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::optional<RType::RGamePack> UDPClient::GetPacket()
	{
		{
			if (m_Packets.empty())
			{
				return {};
			}

			const auto p = m_Packets.front();
			m_Packets.pop();

			return p;
		}
	}

	void UDPClient::OnReceive(const boost::system::error_code& error, const std::size_t& bytes_transferred)
	{
		if (error && error != boost::asio::error::message_size)
		{
			std::cerr << "[UDP::OnReceive] " << error.message() << std::endl;
		}
		else
		{
			// std::cout << "[UDP::OnReceive] " << bytes_transferred << " bytes transferred" << std::endl;

			auto p = RType::RGamePack();

			if (!p.ParseFromArray(m_OutputBuffer.data(), static_cast<int>(bytes_transferred)))
			{
				std::cerr << "[UDP::OnReceive] Failed to parse data. " << bytes_transferred << std::endl;
			}
			else
			{
				if (p.code() == RType::RGamePack::END_GAME)
				{
					std::cout << "[UDP closed] -> Switching scene..." << std::endl;
					m_GameManager->SwitchScene(END_ID);
					return;
				}
				// Send packet to systems.
				m_GameManager->DispatchPacket(p);
			}
			this->ReceiveAsync();
		}
	}

	void UDPClient::Start()
	{
		m_Socket.bind(m_Endpoint);
		this->ReceiveAsync();
		m_Thread = std::thread([ctx = &m_IoContext] { ctx->run(); });
		
		auto packet = RType::RGamePack();
		packet.set_code(RType::RGamePack::PING);
		this->SendAsync(packet);
	}

	void UDPClient::Stop()
	{
		m_Socket.close();
		m_IoContext.stop();

		if (m_Thread.joinable())
		{
			m_Thread.join();
		}
	}
}