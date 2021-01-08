#include <Components/DynamicButton.hpp>

DynamicButton* DynamicButton::Initialize(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texture, const sf::Font& font, const std::string& text, const uint32_t& textSize, const sf::Color& textColor)
{
	m_RectangleShape.setPosition(position);
	m_RectangleShape.setSize(size);
	m_Texture.loadFromFile(texture);
	m_Font = font;
	m_Size = size;
	m_Position = position;
	m_TextSize = textSize;
	m_Text.setString(text);
	m_Text.setCharacterSize(textSize);
	m_Text.setFillColor(textColor);
	m_Text.setFont(m_Font);

	m_RectangleShape.setTexture(&m_Texture);
	m_Text.setPosition({
		position.x + m_RectangleShape.getGlobalBounds().width / 2 - m_Text.getGlobalBounds().width / 2,
		position.y + (m_RectangleShape.getGlobalBounds().height / 2 - m_Text.getGlobalBounds().height / 2 - static_cast<float>(m_TextSize) / 2) });
	
	return this;
}

void DynamicButton::SetLayout(const VerticalLayout& verticalLayout, const Shared<sf::RenderWindow>& window)
{
	m_VerticalLayout = verticalLayout;

	switch (m_VerticalLayout)
	{
		case VerticalLayout::Bottom:
		{
			const auto dimension = window->getSize();

			// TODO: Handle VerticalLayout::Bottom.
			
		} break;
		case VerticalLayout::Center:
		{
			const auto dimension = static_cast<sf::Vector2f>(window->getSize());
			m_RectangleShape.setPosition({ m_Position.x, (dimension.y / 2) - (m_Size.y / 2) });
			
		} break;
		case VerticalLayout::Top:
		{
			const auto dimension = window->getSize();

			// TODO: Handle VerticalLayout::Top.
		} break;
		case VerticalLayout::None:
		{
			// Ignore.
		} break;
	}
}

void DynamicButton::SetLayout(const HorizontalLayout& horizontalLayout, const Shared<sf::RenderWindow>& window)
{
	m_HorizontalLayout = horizontalLayout;

	switch (m_HorizontalLayout)
	{
		case HorizontalLayout::Left:
		{
			// TODO: Handle HorizontalLayout::Left.
		} break;
		case HorizontalLayout::Center:
		{
			const auto dimension = static_cast<sf::Vector2f>(window->getSize());
			m_Position = { (dimension.x / 2) - (m_Size.x / 2), m_Position.y };
			
			m_RectangleShape.setPosition(m_Position);
			m_Text.setPosition({
				m_Position.x + m_RectangleShape.getGlobalBounds().width / 2 - m_Text.getGlobalBounds().width / 2,
				m_Position.y + (m_RectangleShape.getGlobalBounds().height / 2 - m_Text.getGlobalBounds().height / 2 - static_cast<float>(m_TextSize) / 2)
			});
		} break;
		case HorizontalLayout::Right:
		{
			// TODO: Handle HorizontalLayout::Right.
		} break;
		case HorizontalLayout::None:
		{
			// Ignore.
		} break;
	}
}

bool DynamicButton::IsClicked(const sf::Vector2i& mousePosition) const
{
	if (m_RectangleShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		return true;

	return false;
}

void DynamicButton::ExecuteCallback() const
{
	if (m_DefaultCallback)
		m_DefaultCallback();
}

void DynamicButton::SetCallback(const std::function<void()>& callback)
{
	m_DefaultCallback = callback;
}

void DynamicButton::SetState(const bool& state)
{
	m_IsWaitingForInput = state;
}

void DynamicButton::SetInput(const Inputs& input)
{
	m_Input = input;
}

const bool& DynamicButton::GetState() const
{
	return m_IsWaitingForInput;
}

const Inputs& DynamicButton::GetInput() const
{
	return m_Input;
}

const sf::RectangleShape& DynamicButton::GetRectangleShape() const
{
	return m_RectangleShape;
}

const sf::Text& DynamicButton::GetText() const
{
	return m_Text;
}

void DynamicButton::SetText(const std::string& text)
{
	m_Content = text;
	m_Text.setString(m_Content);

	m_Text.setPosition({ m_Position.x + m_RectangleShape.getGlobalBounds().width / 2 - m_Text.getGlobalBounds().width / 2, m_Position.y + (m_RectangleShape.getGlobalBounds().height / 2 - m_Text.getGlobalBounds().height / 2 - m_TextSize / 2) });
}