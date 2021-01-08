#pragma once

#include <string>
#include <RType.Common.hpp>
#include <Models/RGamePack.pb.h>
#include <boost/asio.hpp>

namespace RType
{
    class RTYPECOMMON_API IUDPNetwork
    {
        public:
            virtual ~IUDPNetwork() = default;

        public:
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void SendAsync(RType::RGamePack& p) = 0;
            virtual void SendAsync(RType::RGamePack& p, const std::size_t& id) = 0;
            virtual void ReceiveAsync() = 0;
            virtual void OnReceive(const boost::system::error_code& e, const std::size_t& bytes_transferred) = 0;
    };
}