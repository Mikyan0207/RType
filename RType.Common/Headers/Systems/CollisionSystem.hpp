#pragma once

#include <Systems/System.hpp>
#include <Components/Transform.hpp>
#include <Components/Drawable.hpp>
#include <Components/Monster.hpp>
#include <Managers/GameManager.hpp>

class RTYPECOMMON_API CollisionSystem final : public System<Drawable, Transform>
{
public:
	CollisionSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	CollisionSystem(const CollisionSystem&) = default;
	CollisionSystem(CollisionSystem&&) noexcept = default;
	~CollisionSystem() override = default;

public:
	CollisionSystem& operator=(const CollisionSystem&) = delete;
	CollisionSystem& operator=(CollisionSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;
	void sendCollision(const std::uint32_t &fromId, const std::uint32_t &toId) ;
	void OnPacket(const RType::RGamePack& pack) override;

private:
	Pointer<GameManager> m_GameManager;
	std::vector<Transform*> _playersTransform;
};