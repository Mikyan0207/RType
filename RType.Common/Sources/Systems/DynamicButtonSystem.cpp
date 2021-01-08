#include <Systems/DynamicButtonSystem.hpp>

#include "Helper.hpp"

DynamicButtonSystem::DynamicButtonSystem(const std::size_t& id, const Pointer<GameManager> gameManager) : System<DynamicButton, Text>("DynamicButtonSystem#" + std::to_string(id))
{
	m_GameManager = gameManager;
}

void DynamicButtonSystem::Update(const double& deltaTime)
{
	for (auto&& elem : m_Components)
	{
		auto* dButton = std::get<Pointer<DynamicButton>>(elem);
		auto* dText = std::get<Pointer<Text>>(elem);

		m_GameManager->GetRenderWindow()->draw(dButton->GetRectangleShape());
		m_GameManager->GetRenderWindow()->draw(dButton->GetText());
		m_GameManager->GetRenderWindow()->draw(dText->GetText());
	}
}

void DynamicButtonSystem::OnEvent(sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button != sf::Mouse::Left)
				return;

			for (auto && component : m_Components)
			{
				auto* dButton = std::get<DynamicButton*>(component);

				dButton->SetState(false);

				if (dButton->IsClicked(sf::Mouse::getPosition(*m_GameManager->GetRenderWindow())))
				{
					dButton->SetState(true);
					dButton->SetText("Press any key."); // TODO: Replace with member variable for custom text.
				}
			}
		} break;
		case sf::Event::KeyPressed:
		{
			for (auto && component : m_Components)
			{
				auto* dButton = std::get<DynamicButton*>(component);

				if (dButton->GetState())
				{
					m_GameManager->SetKey(dButton->GetInput(), event.key.code);
					dButton->SetText(Helper::GetKeyAsString(event.key.code));
					dButton->SetState(false);
				}
			}
		} break;
		default:
		{
			// Ignore.
		} break;
	}
}
