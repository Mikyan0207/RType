#pragma once

#include <SFML/Graphics.hpp>

#include <Core.hpp>
#include <Components/Component.hpp>

class RTYPECOMMON_API Sprite : public Component
{
public:
	static constexpr std::size_t Id = 0x0003;

public:
	Sprite() = default;
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) noexcept = default;
	~Sprite() override = default;

public:
	Sprite& operator=(const Sprite&) = default;
	Sprite& operator=(Sprite&&) noexcept = default;

public:
	bool Initialize(const std::string& file, const sf::Vector2f& position, const sf::IntRect& textureRect, const sf::IntRect& spriteRect);

public:
	void SetTexture(sf::Texture& texture, const sf::IntRect & textureRect);
	void SetSpriteColor(const sf::Color& color);
	void SetSpritePosition(const sf::Vector2f& position);
    void SetSpriteScale(const sf::Vector2f& spriteScale);
    void SetSpriteOrigin(const sf::Vector2f& origin);

public:
	[[nodiscard]] const sf::Texture& GetTexture() const;
	[[nodiscard]] sf::Vector2u GetTextureSize() const;
	[[nodiscard]] const sf::Sprite& GetSprite() const;
	[[nodiscard]] const sf::Vector2f& GetSpriteScale() const;
	[[nodiscard]] const sf::Vector2f& GetSpritePosition() const;
	[[nodiscard]] const sf::Vector2f& GetSpriteOrigin() const;
	[[nodiscard]] const sf::Color& GetSpriteColor() const;

protected:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::IntRect m_SpriteRect;
};