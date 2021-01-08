#pragma once

#include <SFML/Graphics.hpp>

#include <Core.hpp>
#include <Components/Component.hpp>
#include <Components/Drawable.hpp>
#include <Components/Transform.hpp>

class RTYPECOMMON_API Parallax final : public Drawable, public Transform
{
public:
	static constexpr std::size_t Id = 12;
	using Transform::SetPosition;
	using Transform::SetRotation;
	using Transform::GetPosition;
	using Transform::GetRotation;
	using Transform::SetScale;
	using Transform::GetScale;

public:
	Parallax(const DrawableType& type, const std::string& file, const sf::IntRect& spriteRect, const sf::IntRect& textureRect = sf::IntRect());
	Parallax(const Parallax&) = default;
	Parallax(Parallax&&) noexcept = default;
	~Parallax() override = default;

public:
	Parallax& operator=(const Parallax&) = delete;
	Parallax& operator=(Parallax&&) noexcept = delete;

public:
	void SetSpeed(const int& speed);

public:
	[[nodiscard]] const int& GetSpeed() const;

public:
	void UpdateParallax();

private:
    int m_Speed;
};