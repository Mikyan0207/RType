#pragma once

#include <Components/Transform.hpp>
#include <Systems/System.hpp>
#include <Managers/GameManager.hpp>

class TransformSystem final : public System<Transform>
{
public:
	explicit TransformSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	TransformSystem(const TransformSystem&) = default;
	TransformSystem(TransformSystem&&) noexcept = default;
	~TransformSystem() override = default;

public:
	TransformSystem& operator=(const TransformSystem&) = delete;
	TransformSystem& operator=(TransformSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnPacket(const RType::RGamePack& pack) override;

private:
	void SendToPlayer(RType::RGamePack& pack, const std::size_t& playerId) const;
	void SendToPlayers(RType::RGamePack& pack) const;

private:
	Pointer<GameManager> m_GameManager;
};