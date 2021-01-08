#pragma once

#include <string>
#include <RType.Common.hpp>
#include <Network/IUDPNetwork.hpp>
#include <Core.hpp>

namespace RType
{
    class RTYPECOMMON_API ITCPNetwork
    {
    public:
        virtual ~ITCPNetwork() = default;

    public:
        virtual void Start() = 0;
        virtual void Stop() = 0;

	public:
        virtual void CreateRoom(const std::uint32_t& maxPlayer) = 0;
        virtual void JoinRoom(const std::string& roomId) = 0;
        virtual void LeaveRoom(const std::string& roomId) = 0;
        virtual void StartGame() = 0;

    public:
    	[[nodiscard]] virtual Shared<IUDPNetwork> GetUdpNetwork() const = 0;
    };
}