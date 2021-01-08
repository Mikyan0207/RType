#include <Components/Parallax.hpp>
#include <Exceptions/RTypeException.hpp>

#include <iostream>

Parallax::Parallax(const DrawableType& type, const std::string& file, const sf::IntRect& spriteRect, const sf::IntRect& textureRect)
: Drawable(type, file, spriteRect, textureRect), Transform({0, 0})
{
    m_Speed = 0;
}

void Parallax::SetSpeed(const int& speed)
{
    m_Speed = speed;
}

const int& Parallax::GetSpeed() const
{
	return m_Speed;
}

void Parallax::UpdateParallax()
{
    if (this->m_SpriteRect.left <= static_cast<int>(m_Texture.getSize().x / 2))
    {
        this->m_SpriteRect.left += this->m_Speed;
    }
    else
    {
        this->m_SpriteRect.left = 0;
    }
    m_Sprite.setTextureRect(m_SpriteRect);
    m_Sprite.setPosition(this->GetPosition());
    m_Sprite.setRotation(this->GetRotation());
    m_Sprite.setScale(this->GetScale());
}