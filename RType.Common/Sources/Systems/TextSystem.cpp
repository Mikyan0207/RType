#include <Systems/TextSystem.hpp>

TextSystem::TextSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window)
	: System<Text>("TextSystem#" + std::to_string(id))
{
	m_RenderWindow = window;
}

void TextSystem::Update(const double& deltaTime)
{
	for (auto &&elem : m_Components)
	{
		auto* text = std::get<Pointer<Text>>(elem);

		m_RenderWindow->draw(text->GetText());
	}
}

void TextSystem::OnEvent(sf::Event& event)
{
}
