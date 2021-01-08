#pragma once

#include <queue>
#include <array>
#include <mutex>
#include <string>
#include <optional>
#include <functional>
#include <boost/asio.hpp>
#include <Models/RTypePack.pb.h>
#include <RType.Common.hpp>
#include <Core.hpp>
#include <Exceptions/RTypeException.hpp>

namespace RType
{
    class RTYPECOMMON_API Connection : public std::enable_shared_from_this<Connection>
    {
    public:
        typedef Shared<Connection> ConnectionPtr;
        static ConnectionPtr Create(boost::asio::io_context& context);

    public:
        explicit Connection(boost::asio::io_context& context);
        ~Connection();

    public:
        void Start();
        void ConnectAsync(boost::asio::io_context &context, const std::string& ip_addr, const std::string& port);
        void ReadAsync();
        void WriteAsync(const RType::RTypePack& p);
        bool IsOpen() const;

    public:
        const std::string& GetLocalIpAddress() const;

    public:
        std::optional<RType::RTypePack> GetPacket();

    private:
        void OnConnect(const boost::system::error_code& error);
        void OnRead(const boost::system::error_code& error, const std::size_t& bytes_transferred);
        void OnWrite(const boost::system::error_code& error, const std::size_t& bytes_transferred);

    public:
        boost::asio::ip::tcp::socket& GetSocket();

    private:
        boost::asio::ip::tcp::socket m_Socket;
        std::string m_LocalIpAddress;
        bool m_IsOpen;
        char m_InputBuffer[1024] = {0};
        std::array<char, 128> m_OutputBuffer = {0};
        std::mutex m_Mutex;
        std::queue<RType::RTypePack> m_PacketsToSend;
        std::queue<RType::RTypePack> m_Packets;
    };
}