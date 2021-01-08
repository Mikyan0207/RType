#pragma once

#include <Systems/System.hpp>
#include <Components/Parallax.hpp>

class RTYPECOMMON_API ParallaxSystem final : public System<Parallax>
{
public:
	explicit ParallaxSystem(const std::size_t& id, const Shared<sf::RenderWindow>&);
	ParallaxSystem(const ParallaxSystem&) = default;
	ParallaxSystem(ParallaxSystem&&) noexcept = default;
	~ParallaxSystem() override = default;

public:
	ParallaxSystem& operator=(const ParallaxSystem&) = delete;
	ParallaxSystem& operator=(ParallaxSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;

private:
	Shared<sf::RenderWindow> m_RenderWindow;
};