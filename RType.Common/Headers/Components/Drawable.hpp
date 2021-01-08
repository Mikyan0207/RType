#pragma once

#include <Components/Component.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Drawable : public virtual Component
{
public:
	static constexpr std::size_t Id = 10;

	enum class DrawableType
	{
		Player,
		Ally,
		Monster,
		Object
	};

public:
    Drawable(const DrawableType& type, const std::string& file, const sf::IntRect& spriteRect, const sf::IntRect& textureRect = sf::IntRect());
    Drawable(const Drawable&) = default;
    Drawable(Drawable&&) noexcept = default;
    ~Drawable() override = default;

public:
    Drawable& operator=(const Drawable&) = default;
    Drawable& operator=(Drawable&&) noexcept = default;

public:
	void Animate(const double& deltaTime);
	
public:
	void SetPosition(const sf::Vector2f& position);
	void SetRotation(const float& rotation);
	void SetScale(const sf::Vector2f& scale);
	void SetAnimated(const bool& animated, const size_t& frameNb, const double& timeRate = 0.2);
	void SetAnimationFrame(const size_t& frame, const double& deltaTime);
	void ResetAnimation();
	
public:
	[[nodiscard]] const sf::Vector2f& GetPosition() const;
	[[nodiscard]] float GetRotation() const;
	[[nodiscard]] sf::FloatRect GetGlobalBounds() const;
	[[nodiscard]] const sf::Sprite& GetSprite() const;
	[[nodiscard]] sf::IntRect GetSpriteRect() const;
	[[nodiscard]] const DrawableType& GetType() const;
	[[nodiscard]] size_t GetCurrentAnimationFrame() const;
	[[nodiscard]] size_t GetAnimationFrameNb() const;
	[[nodiscard]] const sf::Vector2f& GetScale() const;

protected:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::IntRect m_SpriteRect;
	DrawableType m_Type;
	bool m_Animated = false;
	size_t m_AnimFrameNb = 0;
	int m_AnimWay = 1;
	std::pair<double, double> m_AnimTimeRate = {0.0, 200};
};