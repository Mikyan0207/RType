#include <Systems/ParallaxSystem.hpp>

ParallaxSystem::ParallaxSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window) : System<Parallax>("ParallaxSystem#" + std::to_string(id))
{
	m_RenderWindow = window;
}

void ParallaxSystem::Update(const double& deltaTime)
{
	for (auto && component : m_Components)
	{
		auto* parallax = std::get<Pointer<Parallax>>(component);

		parallax->UpdateParallax();

		m_RenderWindow->draw(parallax->GetSprite());
	}
}

void ParallaxSystem::OnEvent(sf::Event& event)
{
}
