#pragma once

#include <Components/Text.hpp>
#include <Systems/System.hpp>

class RTYPECOMMON_API TextSystem final : public System<Text>
{
public:
	TextSystem(const std::size_t & id, const Shared<sf::RenderWindow>& window);
	TextSystem(const TextSystem&) = default;
	TextSystem(TextSystem&&) noexcept = default;
	~TextSystem() override = default;

public:
	TextSystem& operator=(const TextSystem&) = delete;
	TextSystem& operator=(TextSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event & event) override;

private:
	Shared<sf::RenderWindow> m_RenderWindow;
};
