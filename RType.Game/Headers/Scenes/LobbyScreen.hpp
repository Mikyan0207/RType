#pragma once

#include <Scenes/Scene.hpp>

constexpr auto LOBBY_ID = 2;

class LobbyScreen final : public Scene
{
public:
	explicit LobbyScreen(const std::size_t& id);
	LobbyScreen(const LobbyScreen&) = delete;
	LobbyScreen(LobbyScreen&&) noexcept = default;
	~LobbyScreen() override = default;

public:
	LobbyScreen& operator=(const LobbyScreen&) = delete;
	LobbyScreen& operator=(LobbyScreen&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
};