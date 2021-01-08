#include <Components/Text.hpp>

bool Text::Initialize(const std::string& textString, const sf::Vector2f& position, const uint32_t& textSize, const sf::Color& color, const sf::Font& font)
{
	m_Font = font;
	m_Position = position;
	m_TextSize = textSize;
	m_Text.setFillColor(color);
	m_Text.setString(textString);
	m_Text.setFont(m_Font);
	m_Text.setPosition(m_Position);
	m_Text.setCharacterSize(m_TextSize);

	return true;
}

/// <summary>
/// Set or Update Text
/// </summary>
/// <param name="text">The new Text</param>
void Text::SetText(const sf::Text& text)
{
	m_Text = text;
}

/// <summary>
/// Set or Update the text color.
/// </summary>
/// <param name="color">The new text color</param>
void Text::SetTextColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

/// <summary>
/// Set or Update the font.
/// </summary>
/// <param name="font">The new font.</param>
void Text::SetFont(const sf::Font& font)
{
	m_Font = font;
	m_Text.setFont(m_Font);
}

void Text::SetLayout(const HorizontalLayout& horizontalLayout, const Shared<sf::RenderWindow>& window)
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
		const auto textDimension = m_Text.getGlobalBounds();
		m_Position = { (dimension.x / 2) - (textDimension.width / 2), m_Position.y };

		m_Text.setPosition(m_Position);
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

void Text::SetLayout(const VerticalLayout& verticalLayout, const Shared<sf::RenderWindow>& window)
{
}

/// <summary>
/// Set or Update the Text position.
/// </summary>
/// <param name="position">The new position.</param>
void Text::SetTextPosition(const sf::Vector2f& position)
{
	m_Text.setPosition(position);
}

/// <summary>
/// Set or Update Text character size.
/// </summary>
/// <param name="size">The new Text character size.</param>
void Text::SetTextCharSize(const unsigned int& size)
{
	m_Text.setCharacterSize(size);
}

/// <summary>
/// Set or Update Text
/// </summary>
/// <param name="text">The new Text</param>
void Text::SetString(const std::string& text)
{
	m_Text.setString(text);
}

/// <summary>
/// Get the Text.
/// </summary>
/// <returns>Text.</returns>
const sf::Text& Text::GetText() const
{
	return m_Text;
}

/// <summary>
/// Get the Color of the Text.
/// </summary>
/// <returns>Text's color.</returns>
const sf::Color& Text::GetTextColor() const
{
	return m_Text.getFillColor();
}

/// <summary>
/// Get the Font attached to the Text.
/// </summary>
/// <returns>The font of the Text.</returns>
const sf::Font& Text::GetFont() const
{
	return m_Font;
}

std::string Text::GetString() const
{
	return m_Text.getString().toAnsiString();
}

/// <summary>
/// Get the position of the Text.
/// </summary>
/// <returns>Position of the Text as a Vector2f</returns>
const sf::Vector2f& Text::GetTextPosition() const
{
	return m_Text.getPosition();
}

/// <summary>
/// Get the character size of the Text.
/// </summary>
/// <returns>The size of character in the Text.</returns>
std::uint32_t Text::GetTextCharSize() const
{
	return m_Text.getCharacterSize();
}
