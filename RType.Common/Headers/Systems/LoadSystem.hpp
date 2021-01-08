#pragma once

#include <Systems/System.hpp>
#include <Components/Component.hpp>
#include <Managers/GameManager.hpp>

class LoadSystem final : public ISystem
{
public:
	LoadSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	LoadSystem(const LoadSystem&) = default;
	LoadSystem(LoadSystem&&) noexcept = default;
	~LoadSystem() override = default;

public:
	LoadSystem& operator=(const LoadSystem&) = delete;
	LoadSystem& operator=(LoadSystem&&) noexcept = delete;

public:
	void OnEntityCreated(const IEntity& e) override;
	void OnEntityDestroyed(const std::size_t& id) override;
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;
	void OnPacket(const RType::RGamePack& pack) override;

public:
	[[nodiscard]] const std::string& GetId() const override;

private:
	std::string m_Id;
	Pointer<GameManager> m_GameManager;
	std::unordered_map<std::string, sf::Vector2u> m_ShootSizes;
};