#include <DefaultMonster.hpp>
#include <stdexcept>

DefaultMonster::DefaultMonster()
{
	m_Bullets.reserve(1);
	m_Position = { 3.21f, -2.54f };

	m_Bullets.emplace_back(std::make_pair(12.3f, 5.75f));
}

DefaultMonster::DefaultMonster(const DefaultMonster& df)
{
	m_Bullets = df.m_Bullets;
	m_Position = df.m_Position;
}

DefaultMonster::DefaultMonster(DefaultMonster&& df) noexcept
{
	try
	{
		m_Bullets = df.m_Bullets;
		m_Position = df.m_Position;
	}
	catch (const std::exception&)
	{
		// @Silent
	}
}

void DefaultMonster::Initialize()
{
}

void DefaultMonster::Update()
{
	// This function is called every frame.

	// TODO : Update monster position
	// TODO : Update bullets position
}

void DefaultMonster::Destroy()
{
}

void DefaultMonster::SetPosition(const std::pair<float, float>& position)
{
	m_Position = position;
}

const std::pair<float, float>& DefaultMonster::GetPosition() const
{
	return m_Position;
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> DefaultMonster::GetBulletsPosition() const
{
	return m_Bullets;
}

const std::pair<float, float> DefaultMonster::GetBulletPosition(const std::size_t& index) const
{
	if (index > m_Bullets.size())
		throw std::out_of_range("Index is out of range, cannot get bullet position.");

	// TODO : can crash (.at)
	return m_Bullets.at(index).second;
}

std::size_t DefaultMonster::GetBullets() const
{
	return m_Bullets.size();
}

const std::size_t& DefaultMonster::GetId() const
{
	return m_Id;
}
