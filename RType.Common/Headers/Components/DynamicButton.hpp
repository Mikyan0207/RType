#pragma once

#include <functional>
#include <Components/Component.hpp>
#include <SFML/Graphics.hpp>
#include <Managers/Inputs.hpp>

class RTYPECOMMON_API DynamicButton final : public Component
{
public:
	static constexpr std::size_t Id = 0x0007;

public:
	DynamicButton() = default;
	DynamicButton(const DynamicButton&) = default;
	DynamicButton(DynamicButton&&) noexcept = default;
	~DynamicButton() override = default;

public:
	DynamicButton& operator=(const DynamicButton&) = default;
	DynamicButton& operator=(DynamicButton&&) noexcept = default;

public:
	DynamicButton* Initialize(const sf::Vector2f & position, const sf::Vector2f & size, const std::string & texture, const sf::Font & font, const std::string & text, const uint32_t & textSize, const sf::Color & textColor);
	bool IsClicked(const sf::Vector2i & mousePosition) const;
	void ExecuteCallback() const;

public:
	void SetText(const std::string& text);
	void SetLayout(const HorizontalLayout & horizontalLayout, const Shared<sf::RenderWindow> & window);
	void SetLayout(const VerticalLayout & verticalLayout, const Shared<sf::RenderWindow> & window);
	void SetCallback(const std::function<void()> & callback);
	void SetState(const bool& state);
	void SetInput(const Inputs& input);

public:
	[[nodiscard]] const bool& GetState() const;
	[[nodiscard]] const Inputs& GetInput() const;
	[[nodiscard]] const sf::RectangleShape& GetRectangleShape() const;
	[[nodiscard]] const sf::Text& GetText() const;

private:
	sf::Texture m_Texture;
	sf::RectangleShape m_RectangleShape;
	sf::Vector2f m_Offset;
	sf::Vector2f m_Position;
	sf::Vector2f m_Size;
	std::uint32_t m_TextSize;
	sf::Text m_Text;
	sf::Font m_Font;
	std::string m_Content;
	bool m_IsWaitingForInput = false;
	std::function<void()> m_DefaultCallback;
	Inputs m_Input;
};