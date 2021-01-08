#pragma once

#include <unordered_map>
#include <Components/Component.hpp>
#include <Managers/Inputs.hpp>
#include <SFML/Graphics.hpp>

class RTYPECOMMON_API Input final : public Component
{
public:
	static constexpr std::size_t Id = 0x0006;

public:
	Input(const std::unordered_map<Inputs, sf::Keyboard::Key>& keys);
	Input(const Input&) = default;
	Input(Input&&) noexcept = default;
	~Input() override = default;

public:
	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) noexcept = delete;

public:
	void SetKey(const Inputs & input, const sf::Keyboard::Key & key);
	const sf::Keyboard::Key& GetKey(const Inputs&);

private:
	std::unordered_map<Inputs, sf::Keyboard::Key> m_Keys;
};