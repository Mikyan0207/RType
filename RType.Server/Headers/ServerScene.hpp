#pragma once

#include <Scenes/Scene.hpp>
#include <UDPServer.hpp>

class ServerScene final : public Scene
{
public:
	ServerScene(const std::size_t& id, const std::size_t& playerNb);
	ServerScene(const ServerScene&) = delete;
	ServerScene(ServerScene&&) noexcept = delete;
	~ServerScene() override = default;

public:
	ServerScene& operator=(const ServerScene&) = delete;
	ServerScene& operator=(ServerScene&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;

private:
	std::size_t m_PlayerNumber;
};