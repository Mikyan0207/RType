#pragma once
#include <Systems/System.hpp>
#include <Components/Button.hpp>

class RTYPECOMMON_API ButtonSystem final : public System<Button>
{
public:
	ButtonSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window);
	ButtonSystem(const ButtonSystem&) = default;
	ButtonSystem(ButtonSystem&&) noexcept = default;
	~ButtonSystem() override = default;

public:
	ButtonSystem& operator=(const ButtonSystem&);
	ButtonSystem& operator=(ButtonSystem&&) noexcept;

public:
	void Update(const double& deltaTime) final;
	void OnEvent(sf::Event& event) final;

private:
	Shared<sf::RenderWindow> m_RenderWindow;
};