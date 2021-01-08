#pragma once

#include <unordered_map>
#include <Components/Drawable.hpp>
#include <Components/Input.hpp>
#include <Components/Transform.hpp>
#include <Systems/System.hpp>
#include <Managers/Inputs.hpp>
#include <Managers/GameManager.hpp>
#include <Network/IUDPNetwork.hpp>


class RTYPECOMMON_API PlayerSystem final : public System<Drawable, Transform, Input>
{
public:
	PlayerSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	PlayerSystem(const PlayerSystem&) = default;
	PlayerSystem(PlayerSystem&&) noexcept = default;
	~PlayerSystem() override = default;

public:
	PlayerSystem& operator=(const PlayerSystem&) = delete;
	PlayerSystem& operator=(PlayerSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;
	void OnPacket(const RType::RGamePack& pack) override;

public:
	enum AnimationType
	{
		UP,
		DOWN,
		STABILIZE
	};
	void AnimateShip(const AnimationType&, Pointer<Drawable>&, const double& deltaTime);
	
private:
	Pointer<GameManager> m_GameManager;
	std::map<Inputs, bool> m_KeyPressedMap;

private:
	Unique<Drawable> m_LoadAnimation;
	std::pair<double /*Time spent charging*/, size_t /*Shoot level*/> m_ShootLevelInfo;
	bool m_IsLoadingShoot = false;
	
};
