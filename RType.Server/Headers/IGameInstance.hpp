#pragma once

namespace RType
{
    class IGameInstance
    {
        public:
            virtual ~IGameInstance() = default;

        public:
            virtual bool StartGame() = 0;
    };
}