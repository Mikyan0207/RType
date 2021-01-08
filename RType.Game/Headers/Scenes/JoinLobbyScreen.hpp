#pragma once

#include <Scenes/Scene.hpp>

constexpr auto JLS_ID = 5;

class JoinLobbyScreen final : public Scene
{
public:
	explicit JoinLobbyScreen(const std::size_t& id);
	JoinLobbyScreen(const JoinLobbyScreen&) = delete;
	JoinLobbyScreen(JoinLobbyScreen&&) noexcept = default;
	~JoinLobbyScreen() override = default;

public:
	JoinLobbyScreen& operator=(const JoinLobbyScreen&) = delete;
	JoinLobbyScreen& operator=(JoinLobbyScreen&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
};