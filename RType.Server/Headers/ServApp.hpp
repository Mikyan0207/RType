#pragma once

#include <cstdint>

#include <TCPServer.hpp>
#include <Threads/ThreadPool.hpp>
#include <cstdint>

class ServApp
{
    public:
        ServApp();
        ServApp(const ServApp&) = delete;
        ServApp(ServApp&&) noexcept = delete;
        ~ServApp();

    public:
        ServApp& operator=(const ServApp&) = delete;
        ServApp& operator=(ServApp&&) noexcept = delete;

    public:
        void Run();

    private:
        Unique<RType::TCPServer> m_Server;
        Shared<ThreadPool> m_ThreadPool;
};