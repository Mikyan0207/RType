#pragma once

#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include <Components/Component.hpp>
#include <Exceptions/RTypeException.hpp>

class RTYPECOMMON_API Button final : public Component
{
public:
	static constexpr std::size_t Id = 0x0001;

public:
	Button();
	Button(const Button&) = default;
	Button(Button&&) noexcept = default;

public:
	Button& operator=(const Button&) = delete;
	Button& operator=(Button&&) noexcept = delete;

public:
	bool Initialize(const sf::Vector2f& position, const sf::Vector2f& size, const std::string & texture, const sf::Font& font, const std::string& text, const uint32_t& textSize, const sf::Color& textColor);
	bool IsClicked(const sf::Vector2i& mousePosition) const;
	void ExecuteCallback() const;

public:
	void SetRectangleShape(const sf::RectangleShape& rectangleShape);
	void SetBackgroundColor(const sf::Color& color);
	void SetText(const sf::Text& text);
	void SetTextColor(const sf::Color& color);
	void SetFont(const sf::Font& font);
	void SetPosition(const sf::Vector2f& position);
	void SetSize(const sf::Vector2f& size);
	void SetTextString(const std::string& text);
	void SetCallback(const std::function<void()>& callback);

public:
	[[nodiscard]] const sf::RectangleShape& GetRectangleShape() const;
	[[nodiscard]] const sf::Color& GetBackgroundColor() const;
	[[nodiscard]] const sf::Text& GetText() const;
	[[nodiscard]] const sf::Color& GetTextColor() const;
	[[nodiscard]] const sf::Font& GetFont() const;
	[[nodiscard]] const sf::Vector2f& GetPosition() const;
	[[nodiscard]] const sf::Vector2f& GetSize() const;
	[[nodiscard]] const sf::String& GetTextString() const;

private:
	sf::Texture m_Texture;
	sf::RectangleShape m_RectangleShape;
	sf::Text m_Text;
	sf::Font m_Font;
	std::function<void()> m_DefaultCallback;
};