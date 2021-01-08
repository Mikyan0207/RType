#include <Components/Monster.hpp>
#include <iostream>

Monster::Monster(const Shared<IMonster>& monster)
{
	m_Monster = monster;
}

void Monster::Destroy()
{
}

std::optional<std::vector<std::pair<std::uint32_t, std::pair<float, float>>>> Monster::Shoot()
{
	if (m_Clock.getElapsedTime().asSeconds() >= m_Monster->GetShootFrequency())
	{
		auto bullets_to_load = m_Monster->Shoot();
		m_Clock.restart();
		return bullets_to_load;
	}

	return {};
}

void Monster::SetLoaded(const bool& loaded)
{
	Loaded = loaded;
}

const bool& Monster::IsLoaded() const
{
	return Loaded;
}

const Shared<IMonster>& Monster::GetIMonster() const
{
	return m_Monster;
}
