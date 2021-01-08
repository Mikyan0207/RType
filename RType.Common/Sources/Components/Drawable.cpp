#include <Components/Drawable.hpp>

#include "Logger.hpp"

Drawable::Drawable(const DrawableType& type, const std::string& file, const sf::IntRect& spriteRect, const sf::IntRect& textureRect)
{
	// TODO: Check result.
	m_Texture.loadFromFile(file, textureRect);

	m_SpriteRect = spriteRect;
	m_Type = type;

	m_Sprite.setTextureRect(spriteRect);
	m_Sprite.setTexture(m_Texture);
}

void Drawable::Animate(const double& deltaTime)
{
	if (m_Animated == false)
		return;

	m_AnimTimeRate.first += deltaTime;
	if (m_AnimTimeRate.first < m_AnimTimeRate.second)
		return;

	m_AnimTimeRate.first = 0.0;
	m_SpriteRect.left += m_SpriteRect.width * m_AnimWay;
	if (m_SpriteRect.left > static_cast<int>((m_AnimFrameNb - 1) * m_SpriteRect.width)
		|| m_SpriteRect.left < 0)
	{
		m_AnimWay *= (-1);
		m_SpriteRect.left += m_SpriteRect.width * m_AnimWay;
	}
	m_Sprite.setTextureRect(m_SpriteRect);
}

void Drawable::SetPosition(const sf::Vector2f& position)
{
	m_Sprite.setPosition(position);
}

void Drawable::SetRotation(const float& rotation)
{
	m_Sprite.setRotation(rotation);
}

void Drawable::SetScale(const sf::Vector2f& scale)
{
	m_Sprite.setScale(scale);
}

void Drawable::SetAnimated(const bool& animated, const size_t& frameNb, const double& timeRate)
{
	m_Animated = animated;
	m_AnimFrameNb = frameNb;
	m_AnimTimeRate = {0.0, timeRate * 1000.0};
}

void Drawable::SetAnimationFrame(const size_t& frame, const double& deltaTime)
{
	m_AnimTimeRate.first += deltaTime;
	if (m_AnimTimeRate.first < m_AnimTimeRate.second)
		return;

	m_AnimTimeRate.first = 0.0;
	if (frame < m_AnimFrameNb)
	{
		m_SpriteRect.left = static_cast<int>(frame * m_SpriteRect.width);
		m_Sprite.setTextureRect(m_SpriteRect);
	}
}

const sf::Vector2f& Drawable::GetPosition() const
{
	return m_Sprite.getPosition();
}

float Drawable::GetRotation() const
{
	return m_Sprite.getRotation();
}

sf::FloatRect Drawable::GetGlobalBounds() const
{
	return m_Sprite.getGlobalBounds();
}

const sf::Sprite& Drawable::GetSprite() const
{
	return m_Sprite;
}

sf::IntRect Drawable::GetSpriteRect() const
{
	return m_SpriteRect;
}

const Drawable::DrawableType& Drawable::GetType() const
{
	return m_Type;
}

size_t Drawable::GetCurrentAnimationFrame() const
{
	return static_cast<size_t>(m_SpriteRect.left / m_SpriteRect.width);
}

size_t Drawable::GetAnimationFrameNb() const
{
	return m_AnimFrameNb;
}

const sf::Vector2f& Drawable::GetScale() const
{
	return m_Sprite.getScale();
}

void Drawable::ResetAnimation()
{
	m_AnimTimeRate.first = 0.0;
	m_SpriteRect.left = 0;
	m_Sprite.setTextureRect(m_SpriteRect);
}
