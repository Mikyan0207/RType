#include <Components/TextInput.hpp>
#include <Exceptions/RTypeException.hpp>

TextInput& TextInput::operator=(TextInput&& other) noexcept
{
	try
	{
		m_Text = other.m_Text;
		m_RectangleShape = other.m_RectangleShape;
		m_Content = other.m_Content;

		return *this;
	}
	catch (...)
	{
		// @Silent

		return *this;
	}
}

bool TextInput::Initialize(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font)
{
	m_RectangleShape.setSize(size);
	m_RectangleShape.setPosition(position);
	m_RectangleShape.setFillColor(sf::Color(255,255,255,100));
	m_RectangleShape.setOutlineColor(sf::Color(85,85,85));
	m_RectangleShape.setOutlineThickness(0.75f);

	m_Font = font;
	m_Text.setFont(m_Font);
	m_Text.setPosition({position.x, position.y + 2.0f});
	m_Text.setFillColor(sf::Color::Black);
	m_Text.setCharacterSize(40);

	m_Cursor[0] = sf::Vertex(sf::Vector2f(position.x + 3.0f, position.y + 3.0f), sf::Color::Black);
	m_Cursor[1] = sf::Vertex(sf::Vector2f(position.x + 3.0f, position.y + size.y - 3.0f), sf::Color::Black);
	
	return true;
}

 void TextInput::Draw(Shared<sf::RenderWindow>& window)
 {
 	window->draw(m_RectangleShape);
 	window->draw(m_Text);

 	if (!m_IsFocused)
 		return;
	
 	if (m_CursorClock.getElapsedTime().asSeconds() > 0.5f)
 		window->draw(m_Cursor, 2, sf::Lines);

 	if (m_CursorClock.getElapsedTime().asSeconds() > 1.0f)
 		m_CursorClock.restart();
 }

void TextInput::Destroy()
{
}

void TextInput::AppendLetter(const char& letter)
{
	m_Content.push_back(letter);

	m_Text.setString(m_Content);
	const auto textPosition = m_Text.getGlobalBounds();

	m_Cursor[0].position = sf::Vector2f(m_RectangleShape.getPosition().x + textPosition.width + 3.0f, m_Cursor[0].position.y);
	m_Cursor[1].position = sf::Vector2f(m_RectangleShape.getPosition().x + textPosition.width + 3.0f, m_Cursor[1].position.y);
}

void TextInput::RemoveLetter()
{
	if (!m_Content.empty())
	{
		m_Content.pop_back();

		m_Text.setString(m_Content);
		const auto textPosition = m_Text.getGlobalBounds();

		m_Cursor[0].position = sf::Vector2f(m_RectangleShape.getPosition().x + textPosition.width + 3.0f, m_Cursor[0].position.y);
		m_Cursor[1].position = sf::Vector2f(m_RectangleShape.getPosition().x + textPosition.width + 3.0f, m_Cursor[1].position.y);
	}
}

void TextInput::SetFocused(const bool& state)
{
	m_IsFocused = state;
}

const bool& TextInput::IsFocused() const
{
	return m_IsFocused;
}

const std::string& TextInput::GetText() const
{
	return m_Content;
}

bool TextInput::IsClicked(const sf::Vector2i& position) const
{
	if (m_RectangleShape.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(position.x), static_cast<float>(position.y))))
		return true;

	return false;
}
