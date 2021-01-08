#pragma once

#include <Core.hpp>
#include <Components/Component.hpp>
#include <Exceptions/RTypeException.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class RTYPECOMMON_API Text final : public Component
{
public:
	static constexpr std::size_t Id = 0x0002;

public:
	Text() = default;
	Text(const Text&) = default;
	Text(Text&&) noexcept = default;
	~Text() override = default;

public:
	Text& operator=(const Text&) = default;
	Text& operator=(Text&&) noexcept = default;

public:
	bool Initialize(const std::string& textString, const sf::Vector2f& position, const uint32_t & textSize, const sf::Color & color, const sf::Font & font);

public:
	void SetText(const sf::Text& text);
    void SetTextColor(const sf::Color& color);
	void SetTextPosition(const sf::Vector2f& position);
	void SetTextCharSize(const unsigned int& size);
	void SetString(const std::string & text);
	void SetFont(const sf::Font& font);
	void SetLayout(const HorizontalLayout & horizontalLayout, const Shared<sf::RenderWindow> & window);
	void SetLayout(const VerticalLayout & verticalLayout, const Shared<sf::RenderWindow> & window);

public:
	[[nodiscard]] const sf::Text& GetText() const;
	[[nodiscard]] const sf::Color& GetTextColor() const;
	[[nodiscard]] const sf::Vector2f& GetTextPosition() const;
	[[nodiscard]] std::uint32_t GetTextCharSize() const;
	[[nodiscard]] const sf::Font& GetFont() const;
	[[nodiscard]] std::string GetString() const;

private:
	sf::Text m_Text;
	sf::Font m_Font;
	sf::Vector2f m_Position;
	std::uint32_t m_TextSize;
};