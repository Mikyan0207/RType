#pragma once

#include <Models/RTypePack.pb.h>
#include <RType.Common.hpp>

namespace RType
{
    class RTYPECOMMON_API IPacketManager
    {
        public:
            virtual ~IPacketManager() = default;

        public:
            virtual void Initialize() = 0;
            virtual void CallbackHandler(const RType::RTypePack &) = 0;
    };
}