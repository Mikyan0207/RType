#pragma once

#include <Scenes/Scene.hpp>

constexpr auto OPTIONS_ID = 4;

class OptionsScreen final : public Scene
{
public:
	explicit OptionsScreen(const std::size_t& id);
	OptionsScreen(const OptionsScreen&) = delete;
	OptionsScreen(OptionsScreen&&) noexcept = default;
	~OptionsScreen() override = default;

public:
	OptionsScreen& operator=(const OptionsScreen&) = delete;
	OptionsScreen& operator=(OptionsScreen&&) noexcept = delete;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
};