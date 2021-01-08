#include <Components/Button.hpp>

#include "Managers/GameManager.hpp"

Button::Button()
{
	m_EntityId = 0;
}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="size"></param>
/// <param name="texture"></param>
/// <param name="font"></param>
/// <param name="text"></param>
/// <param name="textSize"></param>
/// <param name="textColor"></param>
/// <returns></returns>
bool Button::Initialize(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texture, const sf::Font& font, const std::string& text, const uint32_t& textSize, const sf::Color& textColor)
{
	m_RectangleShape.setPosition(position);
	m_RectangleShape.setSize(size);
	m_Texture.loadFromFile(texture);
	m_Font = font;
	m_Text.setString(text);
	m_Text.setCharacterSize(textSize);
	m_Text.setFillColor(textColor);
	m_Text.setFont(m_Font);
	
	m_Text.setPosition({position.x + m_RectangleShape.getGlobalBounds().width / 2 - m_Text.getGlobalBounds().width / 2, position.y + (m_RectangleShape.getGlobalBounds().height / 2 - m_Text.getGlobalBounds().height / 2 - textSize / 2) });
	m_RectangleShape.setTexture(&m_Texture);

	return true;
}


bool Button::IsClicked(const sf::Vector2i& mousePosition) const
{
	if (m_RectangleShape.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))))
		return true;

	return false;
}

void Button::ExecuteCallback() const
{
	if (m_DefaultCallback)
		m_DefaultCallback();
}

/// <summary>
/// Set or Update button shape
/// </summary>
/// <param name="rectangleShape">The new rectangle shape</param>
void Button::SetRectangleShape(const sf::RectangleShape& rectangleShape)
{
	m_RectangleShape = rectangleShape;
}

/// <summary>
/// Set or Update background color
/// </summary>
/// <param name="color">The new background color</param>
void Button::SetBackgroundColor(const sf::Color& color)
{
	m_RectangleShape.setFillColor(color);
}

/// <summary>
/// Set or Update button text.
/// </summary>
/// <param name="text">The new text</param>
void Button::SetText(const sf::Text& text)
{
	m_Text = text;
}

/// <summary>
/// Set or Update the text color.
/// </summary>
/// <param name="color">The new text color</param>
void Button::SetTextColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

/// <summary>
/// Set or Update the font.
/// </summary>
/// <param name="font">The new font.</param>
void Button::SetFont(const sf::Font& font)
{
	m_Font = font;
	m_Text.setFont(m_Font);
}

/// <summary>
/// Set or Update the button position.
/// </summary>
/// <param name="position">The new position.</param>
void Button::SetPosition(const sf::Vector2f& position)
{
	m_RectangleShape.setPosition(position);
}

/// <summary>
/// Set or Update button size.
/// </summary>
/// <param name="size">The new button size.</param>
void Button::SetSize(const sf::Vector2f& size)
{
	m_RectangleShape.setSize(size);
}

/// <summary>
/// Set or Update the text displayed on the button.
/// </summary>
/// <param name="text">The new text to display.</param>
void Button::SetTextString(const std::string& text)
{
	m_Text.setString(text);
}

/// <summary>
/// 
/// </summary>
/// <param name="callback"></param>
void Button::SetCallback(const std::function<void()>& callback)
{
	m_DefaultCallback = callback;
}

/// <summary>
/// Get the RectangleShape attached to the button.
/// </summary>
/// <returns>RectangleShape of the button.</returns>
const sf::RectangleShape& Button::GetRectangleShape() const
{
	return m_RectangleShape;
}

/// <summary>
/// Get the background color of the button.
/// </summary>
/// <returns>The background color of the button.</returns>
const sf::Color& Button::GetBackgroundColor() const
{
	return m_RectangleShape.getFillColor();
}

/// <summary>
/// Get the Text attached to the button.
/// </summary>
/// <returns>Text of the button.</returns>
const sf::Text& Button::GetText() const
{
	return m_Text;
}

/// <summary>
/// Get the Color of the button.
/// </summary>
/// <returns>Button's color.</returns>
const sf::Color& Button::GetTextColor() const
{
	return m_Text.getFillColor();
}

/// <summary>
/// Get the Font attached to the button.
/// </summary>
/// <returns>The font of the button.</returns>
const sf::Font& Button::GetFont() const
{
	return m_Font;
}

/// <summary>
/// Get the position of the button.
/// </summary>
/// <returns>Position of the Button as a Vector2f</returns>
const sf::Vector2f& Button::GetPosition() const
{
	return m_RectangleShape.getPosition();
}

/// <summary>
/// Get the size of the button.
/// </summary>
/// <returns>The size of button.</returns>
const sf::Vector2f& Button::GetSize() const
{
	return m_RectangleShape.getSize();
}

/// <summary>
/// Get the text displayed on the button.
/// </summary>
/// <returns>Get the text of the button.</returns>
const sf::String& Button::GetTextString() const
{
	return m_Text.getString();
}
