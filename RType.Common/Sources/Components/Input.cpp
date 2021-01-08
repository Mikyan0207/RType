#include <Components/Input.hpp>

Input::Input(const std::unordered_map<Inputs, sf::Keyboard::Key>& keys)
{
	m_Keys[Inputs::Up] = keys.at(Inputs::Up);
	m_Keys[Inputs::Left] = keys.at(Inputs::Left);
	m_Keys[Inputs::Down] = keys.at(Inputs::Down);
	m_Keys[Inputs::Right] = keys.at(Inputs::Right);
	m_Keys[Inputs::Shoot] = keys.at(Inputs::Shoot);
}

void Input::SetKey(const Inputs& input, const sf::Keyboard::Key& key)
{
	m_Keys[input] = key;
}

const sf::Keyboard::Key& Input::GetKey(const Inputs& input)
{
	return m_Keys[input];
}
