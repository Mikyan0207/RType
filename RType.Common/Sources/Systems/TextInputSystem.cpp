#include <Systems/TextInputSystem.hpp>

TextInputSystem::TextInputSystem(const std::size_t& id, const Shared<sf::RenderWindow>& window) : System<TextInput>("TextSystem#" + std::to_string(id))
{
	m_RenderWindow = window;
}

TextInputSystem& TextInputSystem::operator=(const TextInputSystem& other)
{
	m_Components = other.m_Components;
	m_EntityIdToIndex = other.m_EntityIdToIndex;

	return *this;
}

TextInputSystem& TextInputSystem::operator=(TextInputSystem&& other) noexcept
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

void TextInputSystem::Update(const double& deltaTime)
{
	for (auto&& elem : m_Components)
	{
		auto* tInput = std::get<Pointer<TextInput>>(elem);

		tInput->Draw(m_RenderWindow);
	}
}

void TextInputSystem::OnEvent(sf::Event& event)
{
	switch (event.type)  // NOLINT(clang-diagnostic-switch-enum)
	{
		case sf::Event::KeyPressed:
		{
			if (event.key.code != sf::Keyboard::BackSpace)
				return;

			for (auto&& component : m_Components)
			{
				auto* textInput = std::get<TextInput*>(component);

				// Only update focused text input.
				if (textInput->IsFocused())
					textInput->RemoveLetter();
			}
		} break;
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button != sf::Mouse::Left)
				return;
			
			for (auto&& component : m_Components)
			{
				auto* textInput = std::get<TextInput*>(component);

				// Reset TextInput state for security.
				textInput->SetFocused(false);
				if (textInput->IsClicked(sf::Mouse::getPosition(*m_RenderWindow)))
				{
					if (!textInput->IsFocused())
						textInput->SetFocused(true);
				}
			}
		} break;
		case sf::Event::TextEntered:
		{
			if (std::isprint(event.text.unicode))
			{
				for (auto&& component : m_Components)
				{
					auto* textInput = std::get<TextInput*>(component);

					if (textInput->IsFocused())
						textInput->AppendLetter(static_cast<char>(std::toupper(static_cast<int>(event.text.unicode))));
				}
			}
		} break;
		default:
		{
			// Event ignored.
		} break;
	}
}
