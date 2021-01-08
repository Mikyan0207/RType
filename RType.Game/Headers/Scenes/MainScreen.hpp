#pragma once

#include <Scenes/Scene.hpp>

constexpr auto HOME_ID = 1;

class MainScreen final : public Scene
{
public:
	explicit MainScreen(const std::size_t& id);
	MainScreen(const MainScreen&) = delete;
	MainScreen(MainScreen&&) noexcept = default;
	~MainScreen() override = default;

public:
	MainScreen& operator=(const MainScreen&) = delete;
	MainScreen& operator=(MainScreen&&) noexcept = delete;

public:
    void OnCreate(Pointer<GameManager> gameManager) override;
};