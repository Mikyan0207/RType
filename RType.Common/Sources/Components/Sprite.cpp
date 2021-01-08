#include <Components/Sprite.hpp>
#include <Exceptions/RTypeException.hpp>

/// <summary>
/// Initialize a new Text
/// </summary> 
/// <param name="file">Options used for Text creation</param>
/// <param name="position"></param>
/// <param name="textureRect">Size of texture.</param>
/// <param name="spriteRect"></param>
/// <returns>True if text was successfully created, false otherwise.</returns>
bool Sprite::Initialize(const std::string& file, const sf::Vector2f& position, const sf::IntRect& textureRect, const sf::IntRect& spriteRect)
{

	if (textureRect.width == 0 && textureRect.height == 0)
	{
		if (!m_Texture.loadFromFile(file))
			return false;
	}
	else
	{
		if (!m_Texture.loadFromFile(file, textureRect))
			return false;
	}

	m_SpriteRect = spriteRect;
	m_Sprite.setTextureRect(spriteRect);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(position);
	return true;
}

/// <summary>
/// Set or Update Texture
/// </summary>
/// <param name="texture">The new Texture.</param>
/// <param name="textureRect">Size of texture.</param>
void Sprite::SetTexture(sf::Texture& texture, const sf::IntRect& textureRect)
{
	m_Texture = texture;
	m_Sprite.setTextureRect(textureRect);
	m_Sprite.setTexture(m_Texture);
}

/// <summary>
/// Set or Update the Text position.
/// </summary>
/// <param name="position">The new position.</param>
void Sprite::SetSpritePosition(const sf::Vector2f& position)
{
	m_Sprite.setPosition(position);
}

/// <summary>
/// Set or Update Sprite Color
/// </summary>
/// <param name="color">The new Sprite Color</param>
void Sprite::SetSpriteColor(const sf::Color& color)
{
	m_Sprite.setColor(color);
}

/// <summary>
/// Set or Update Sprite Scale
/// </summary>
/// <param name="spriteScale">The new Scale Sprite</param>
void Sprite::SetSpriteScale(const sf::Vector2f& spriteScale)
{
	m_Sprite.scale(spriteScale);
}

/// <summary>
/// Set or Update origin point of the sprite
/// </summary>
/// <param name="origin">The new Sprite Origin.</param>
void Sprite::SetSpriteOrigin(const sf::Vector2f& origin)
{
	m_Sprite.setOrigin(origin);
}

/// <summary>
/// Get the Texture
/// </summary>
/// <returns>Texture.</returns>
const sf::Texture& Sprite::GetTexture() const
{
	return m_Texture;
}

/// <summary>
/// Get the Color of the sprite.
/// </summary>
/// <returns>sprite's color.</returns>
const sf::Color& Sprite::GetSpriteColor() const
{
	return m_Sprite.getColor();
}


/// <summary>
/// Get the size of the texture.
/// </summary>
/// <returns>The size of the Sprite.</returns>
sf::Vector2u Sprite::GetTextureSize() const
{
	return m_Texture.getSize();
}

/// <summary>
/// Get the Scale of the sprite.
/// </summary>
/// <returns>Scale of the sprite as a Vector2f</returns>
const sf::Vector2f& Sprite::GetSpriteScale() const
{
	return m_Sprite.getScale();
}

/// <summary>
/// Get the Sprite
/// </summary>
/// <returns>Sprite</returns>
const sf::Sprite& Sprite::GetSprite() const
{
	return m_Sprite;
}

/// <summary>
/// Get the Sprite Position.
/// </summary>
/// <returns>Position's sprite</returns>
const sf::Vector2f& Sprite::GetSpritePosition() const
{
	return m_Sprite.getPosition();
}

/// <summary>
/// Get the Origin of the sprite.
/// </summary>
/// <returns>origin sprite</returns>
const sf::Vector2f& Sprite::GetSpriteOrigin() const
{
	return m_Sprite.getOrigin();
}
