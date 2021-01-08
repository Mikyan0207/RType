#include <UDPServer.hpp>
#include <Logger.hpp>
#include <utility>

using boost::asio::ip::udp;

namespace RType
{
    UDPServer::UDPServer(std::string ipAddress, const std::uint32_t& port)
        : m_Socket(m_IoContext), m_IpAddress(std::move(ipAddress)), m_Port(port)
    {
        udp::resolver resolver(m_IoContext);
        const udp::resolver::query query(udp::v4(), m_IpAddress, std::to_string(m_Port));
        const udp::resolver::iterator iter = resolver.resolve(query);

        m_ServerEndpoint = *iter;
        m_Socket.open(udp::v4());
    }

	UDPServer::~UDPServer()
	{
		try
		{
			Stop();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

    void UDPServer::Bind()
    {
        m_Socket.bind(m_ServerEndpoint);
    }

    void UDPServer::Start()
    {
        this->Bind();
        this->ReceiveAsync();
        m_Thread = std::thread([ctx = &m_IoContext] { ctx->run(); });
    }

	void UDPServer::Stop()
	{
		m_Socket.close();
		m_IoContext.stop();

		if (m_Thread.joinable())
		{
			m_Thread.join();
		}
	}

    void UDPServer::SendAsync(RType::RGamePack& p)
    {
        for (auto &&[id, endpoint] : m_EndpointMap)
        {
            try
            {
                // Logger::Log("[UDP::Send]");
                if (!p.SerializeToArray(m_InputBuffer, p.ByteSizeLong()))
                {
                    std::cerr << "\t[UDP::Send] - Failed to Serialize" << std::endl;
                    return;
                }
                m_Socket.async_send_to(
                    boost::asio::buffer(m_InputBuffer, p.ByteSizeLong()), endpoint,
                    [=](const boost::system::error_code& error, const std::size_t& bytes_transferred)
                    {
                        if (error)
                        {
                            std::cerr << "\t[UDP::Send] : " << error.message() << std::endl;
                        }
                        else
                        {
                            // Logger::Log("\t[UDP::Send] " + std::to_string(bytes_transferred) + " bytes transferred.");
                        }
                    });
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
    	}
    }

	void UDPServer::SendAsync(RType::RGamePack& p, const std::size_t& id)
	{
		try
		{
			if (!p.SerializeToArray(m_InputBuffer, p.ByteSizeLong()))
			{
				std::cerr << "\t[UDP::Send] - Failed to Serialize" << std::endl;
				return;
			}

			//for (auto & [id, endpoint] : m_EndpointMap)
			//{
                // Logger::Log(std::to_string(id) + " " + endpoint.address().to_string());
			//}
			m_Socket.async_send_to(
				boost::asio::buffer(m_InputBuffer, p.ByteSizeLong()), m_EndpointMap[id],
				[=](const boost::system::error_code& error, const std::size_t& bytes_transferred)
				{
					if (error)
					{
						std::cerr << "\t[UDP::Send] : " << error.message() << std::endl;
					}
					else
					{
						// Logger::Log("\t[UDP::Send] " + std::to_string(bytes_transferred) + " bytes transferred.");
					}
				});
		}
		catch (...)
		{
			
		}
	}

    void UDPServer::ReceiveAsync()
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

    void UDPServer::OnReceive(const boost::system::error_code& error, const std::size_t& bytes_transferred)
    {
        // Logger::Log("[UDP::OnReceive]");

        if (error && error != boost::asio::error::message_size)
        {
            std::cerr << "\t[UDP::OnReceive] " << error.message() << std::endl;
        }
        else
        {
            auto p = RType::RGamePack();

            if (!p.ParseFromArray(m_OutputBuffer.data(), static_cast<int>(bytes_transferred)))
            {
                std::cerr << "\t[UDP::OnReceive] Failed to parse data." << std::endl;
                ReceiveAsync();
                return;
            }

        	if (std::find_if(
                m_EndpointMap.begin(), m_EndpointMap.end(),
                [p](const auto& elem)
                {
                    return elem.first == p.playerid();
                }) == m_EndpointMap.end())
            {
                m_EndpointMap.insert(std::make_pair(static_cast<std::uint32_t>(p.playerid()), std::move(m_Endpoint)));
			}
			// Logger::Log("\t[UDP::OnReceive] " + std::to_string(bytes_transferred) + " bytes transferred");

			if (m_OnReceiveCallback)
				m_OnReceiveCallback(p);
			ReceiveAsync();
		}
	}

    void UDPServer::SetOnReceiveCallback(const std::function<void(const RType::RGamePack&)>& function)
    {
    	m_OnReceiveCallback = function;
    }
}
