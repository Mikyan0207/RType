#pragma once

#include <Components/Component.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Transform : public virtual Component
{
public:
	static constexpr std::size_t Id = 11;
public:
	Transform(const sf::Vector2f& position, const float& rotation = 0, const sf::Vector2f& scale = sf::Vector2f(1,1));
	Transform(const Transform&) = default;
	Transform(Transform&&) noexcept = default;
	~Transform() override = default;

public:
	Transform& operator=(const Transform&) = delete;
	Transform& operator=(Transform&&) noexcept = delete;

public:
	void SetPosition(const sf::Vector2f& position);
	void SetScale(const sf::Vector2f& scale);
	void SetRotation(const float& rotation);
	void SetVelocity(const double& velocity);
	void SetRect(const sf::FloatRect& rect);

public:
	[[nodiscard]] const sf::Vector2f& GetPosition() const;
	[[nodiscard]] const sf::Vector2f& GetScale() const;
	[[nodiscard]] const float& GetRotation() const;
	[[nodiscard]] const double& GetVelocity() const;
	[[nodiscard]] const sf::FloatRect& GetRect() const;
	
protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Scale;
	sf::FloatRect m_Rect;
	float m_Rotation;
	double m_Velocity = 0;
};