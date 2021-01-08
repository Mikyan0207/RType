#include <Systems/ButtonSystem.hpp>
#include <Managers/GameManager.hpp>

ButtonSystem::ButtonSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window) : System<Button>("ButtonSystem#" + std::to_string(id))
{
	m_RenderWindow = window;
}

ButtonSystem& ButtonSystem::operator=(const ButtonSystem& other)
{
	m_Components = other.m_Components;
	m_EntityIdToIndex = other.m_EntityIdToIndex;

	return *this;
}

ButtonSystem& ButtonSystem::operator=(ButtonSystem&& other) noexcept
{
	try
	{
		m_Components = other.m_Components;
		m_EntityIdToIndex = other.m_EntityIdToIndex;

		return *this;
	}
	catch (...)
	{
		// @Silent
		return *this;
	}
}

void ButtonSystem::Update(const double& deltaTime)
{
	for (auto && component : m_Components)
	{
		auto* button = std::get<Pointer<Button>>(component);

		m_RenderWindow->draw(button->GetRectangleShape());
		m_RenderWindow->draw(button->GetText());
	}
}

void ButtonSystem::OnEvent(sf::Event& event)
{
	if (event.type != sf::Event::MouseButtonPressed)
		return;

	for (auto && component : m_Components)
	{
		const auto* btn = std::get<Button*>(component);

		if (btn->IsClicked(sf::Mouse::getPosition(*m_RenderWindow)))
		{
			btn->ExecuteCallback();
		}
	}
}
