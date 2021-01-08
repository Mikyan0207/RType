#pragma once

#include <Components/Drawable.hpp>
#include <Components/Transform.hpp>
#include <Systems/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Managers/GameManager.hpp>

class DrawableSystem final : public System<Drawable, Transform>
{
public:
	DrawableSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	DrawableSystem(const DrawableSystem&) = default;
	DrawableSystem(DrawableSystem&&) noexcept = default;
	~DrawableSystem() override = default;

public:
	DrawableSystem& operator=(const DrawableSystem&) = delete;
	DrawableSystem& operator=(DrawableSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnPacket(const RType::RGamePack& pack) override;

private:
	Pointer<GameManager> m_GameManager;
};