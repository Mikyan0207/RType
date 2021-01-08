#pragma once

#include <Systems/System.hpp>
#include <Components/DynamicButton.hpp>
#include <Components/Text.hpp>
#include <Managers/GameManager.hpp>

class RTYPECOMMON_API DynamicButtonSystem final : public System<DynamicButton, Text>
{
public:
	explicit DynamicButtonSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	DynamicButtonSystem(const DynamicButtonSystem&) = default;
	DynamicButtonSystem(DynamicButtonSystem&&) noexcept = default;
	~DynamicButtonSystem() override = default;

public:
	DynamicButtonSystem& operator=(const DynamicButtonSystem&) = delete;
	DynamicButtonSystem& operator=(DynamicButtonSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;


private:
	Pointer<GameManager> m_GameManager;
};