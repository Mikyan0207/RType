#pragma once
#include <Scenes/Scene.hpp>

constexpr auto GAME_ID = 3;

class GameScreen final : public Scene
{
public:
	explicit GameScreen(const std::size_t& id);
	GameScreen(const GameScreen&) = delete;
	GameScreen(GameScreen&&) noexcept = default;
	~GameScreen() override = default;

public:
	GameScreen& operator=(const GameScreen&) = delete;
	GameScreen& operator=(GameScreen&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
};
