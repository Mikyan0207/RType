#include <Components/Transform.hpp>

Transform::Transform(const sf::Vector2f& position, const float& rotation, const sf::Vector2f& scale)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;
}

void Transform::SetPosition(const sf::Vector2f& position)
{
	m_Position = position;
}

void Transform::SetScale(const sf::Vector2f& scale)
{
	m_Scale = scale;
}

void Transform::SetRotation(const float& rotation)
{
	m_Rotation = rotation;
}

void Transform::SetVelocity(const double& velocity)
{
	m_Velocity = velocity;
}

void Transform::SetRect(const sf::FloatRect& rect)
{
	m_Rect = rect;
}

const sf::Vector2f& Transform::GetPosition() const
{
	return m_Position;
}

const sf::Vector2f& Transform::GetScale() const
{
	return m_Scale;
}

const float& Transform::GetRotation() const
{
	return m_Rotation;
}

const sf::FloatRect& Transform::GetRect() const
{
	return m_Rect;
}

const double& Transform::GetVelocity() const
{
	return m_Velocity;
}
