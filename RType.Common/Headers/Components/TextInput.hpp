#pragma once

#include <SFML/Graphics.hpp>
#include <RType.Common.hpp>
#include <Components/Component.hpp>

class RTYPECOMMON_API TextInput final : public Component
{
public:
	static constexpr std::size_t Id = 0x0005;

public:
	TextInput() = default;
	TextInput(const TextInput&) = default;
	TextInput(TextInput&&) noexcept = default;
	~TextInput() override = default;

public:
	TextInput& operator=(const TextInput&) = default;
	TextInput& operator=(TextInput&&) noexcept;

public:
	bool Initialize(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font & font);
	void Destroy() override;
	void AppendLetter(const char& letter);
	void RemoveLetter();
	void Draw(Shared<sf::RenderWindow> & window);

public:
	void SetFocused(const bool& state);
	
public:
	[[nodiscard]] const bool& IsFocused() const;
	[[nodiscard]] const std::string& GetText() const;
	bool IsClicked(const sf::Vector2i& position) const;

private:
	sf::Text m_Text;
	sf::Font m_Font;
	sf::RectangleShape m_RectangleShape;
	sf::Vertex m_Cursor[2];
	sf::Clock m_CursorClock;
	std::string m_Content;
	bool m_IsFocused = false;
};