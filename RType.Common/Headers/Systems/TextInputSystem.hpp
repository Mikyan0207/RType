#pragma once

#include <Components/TextInput.hpp>
#include <Systems/System.hpp>

class GameManager;

class RTYPECOMMON_API TextInputSystem final : public System<TextInput>
{
public:
	TextInputSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window);
	TextInputSystem(const TextInputSystem&) = default;
	TextInputSystem(TextInputSystem&&) noexcept = default;
	~TextInputSystem() override = default;

public:
	TextInputSystem& operator=(const TextInputSystem&);
	TextInputSystem& operator=(TextInputSystem&&) noexcept;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;

private:
	Shared<sf::RenderWindow> m_RenderWindow;
};
