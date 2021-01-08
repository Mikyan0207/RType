#include <Network/Connection.hpp>
#include <iostream>

namespace RType
{
    Connection::ConnectionPtr Connection::Create(boost::asio::io_context& context)
    {
        return std::make_shared<Connection>(context);
    }

    Connection::Connection(boost::asio::io_context& context) : m_Socket(context)
    {
        m_IsOpen = true;
    }

    Connection::~Connection()
    {
    	try
    	{
            m_Socket.close();
    	}
    	catch (const std::exception&)
    	{
    		// @Silent
    	}
    }

    void Connection::Start()
    {
        // ¯\_(ツ)_/¯
        m_LocalIpAddress = m_Socket.local_endpoint().address().to_string();
    }

    void Connection::ConnectAsync(boost::asio::io_context &context, const std::string& ip_addr, const std::string& port)
    {
        boost::asio::ip::tcp::resolver resolver(context);
        const auto endpoints = resolver.resolve(ip_addr, port);

        m_Socket.async_connect(endpoints->endpoint(),
			[self = shared_from_this()](const boost::system::error_code& error)
			{
				self->OnConnect(error);
			});
    }

    void Connection::ReadAsync()
    {
        boost::asio::async_read(m_Socket, boost::asio::buffer(m_OutputBuffer), boost::asio::transfer_at_least(2),
            [self = shared_from_this()](const boost::system::error_code& error, const std::size_t& bytes_transferred)
            {
                self->OnRead(error, bytes_transferred);
            });
    }

    void Connection::WriteAsync(const RType::RTypePack& p)
    {
        m_Mutex.lock();
        m_PacketsToSend.push(p);
        m_Mutex.unlock();

        if (!m_PacketsToSend.back().SerializeToArray(m_InputBuffer, m_PacketsToSend.back().ByteSizeLong()))
        {
            std::cerr << "[WriteAsync] - Failed to Serialize" << std::endl;
            return;
        }

        boost::asio::async_write(m_Socket, boost::asio::buffer(m_InputBuffer, m_PacketsToSend.back().ByteSizeLong()),
            [self = shared_from_this()](const boost::system::error_code& error, const std::size_t& bytes_transferred)
        {
            self->OnWrite(error, bytes_transferred);
        });
    }

    bool Connection::IsOpen() const
    {
        return m_IsOpen;
    }

    const std::string& Connection::GetLocalIpAddress() const
    {
        return m_LocalIpAddress;
    }

    std::optional<RType::RTypePack> Connection::GetPacket()
    {
        if (m_Packets.empty())
            return {};

        const auto p = m_Packets.front();
        m_Packets.pop();

        return p;
    }

    void Connection::OnConnect(const boost::system::error_code& error)
    {
        if (error)
        {
            std::cerr << "[OnConnect] Error connecting..." << std::endl;
            if (error == boost::asio::error::connection_reset || error == boost::asio::error::eof)
            {
                m_Socket.close();
                m_IsOpen = false;
            }
            throw RTypeException(typeid(Connection).name(), error.message());
        }
        else
        {
            std::cout << "[OnConnect] Connected." << std::endl;
            this->ReadAsync();
        }
    }

    void Connection::OnRead(const boost::system::error_code& error, const std::size_t& bytes_transferred)
    {
        if (error)
        {
            if (error == boost::asio::error::connection_reset || error == boost::asio::error::eof)
            {
                m_Socket.close();
                m_IsOpen = false;
            }
            std::cerr << "[OnRead] " << error.message() << std::endl;
        }
        else
        {
            std::cout << "[OnRead] " << bytes_transferred << " bytes transferred" << std::endl;

            RType::RTypePack p;

            if (!p.ParseFromArray(m_OutputBuffer.data(), static_cast<int>(bytes_transferred)))
            {
                std::cerr << "[OnRead] Failed to parse data." << std::endl;
                return;
            }

            m_Packets.push(std::move(p));
            ReadAsync();
        }
    }

    void Connection::OnWrite(const boost::system::error_code& error, const std::size_t& bytes_transferred)
    {
        std::cerr << "[OnWrite]" << std::endl;
        if (error)
        {
            std::cerr << "[OnWrite] " << error.message() << std::endl;
        }
        else
        {
            std::cerr << "[OnWrite] " << bytes_transferred << " bytes transferred" << std::endl;
            m_Mutex.lock();
            m_PacketsToSend.pop();
            m_Mutex.unlock();
        }
    }

    boost::asio::ip::tcp::socket& Connection::GetSocket()
    {
        return m_Socket;
    }
}