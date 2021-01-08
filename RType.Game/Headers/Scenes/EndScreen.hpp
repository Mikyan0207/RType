#pragma once
#include <Scenes/Scene.hpp>

constexpr auto END_ID = 6;

class EndScreen final : public Scene
{
public:
	explicit EndScreen(const std::size_t& id);
	EndScreen(const EndScreen&) = delete;
	EndScreen(EndScreen&&) noexcept = default;
	~EndScreen() override = default;

public:
	EndScreen& operator=(const EndScreen&) = delete;
	EndScreen& operator=(EndScreen&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
};
