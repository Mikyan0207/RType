#pragma once

#include <Core.hpp>
#include <Managers/GameManager.hpp>
#include <TCPClient.hpp>


class Application
{
public:
    Application(const std::string& ip, const std::int32_t& port);
    Application(const Application&) = delete;
    Application(Application&&) noexcept = delete;
	~Application() = default;

public:
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

public:
    void Run() const;

private:
    Shared<sf::RenderWindow> m_Window;
    Unique<GameManager> m_GameManager;
    Shared<RType::TCPClient> m_Client;
};
