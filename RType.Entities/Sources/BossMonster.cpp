#include <BossMonster.hpp>
#include <BulletBoss.hpp>
#include <stdexcept>

#include "Core.hpp"

BossMonster::BossMonster()
{
	m_Id = 10005;
	m_PowerType = PowerType::None;
	m_BulletRangeId = m_Id + 1;
	m_Filename = "LinearShootingMonster.png";
	m_BulletFilename = "LinearShootingMonster_Bullet.png";
	m_ShootFrequency = 0;
	m_Position = { SCREEN_WIDTH + 200, SCREEN_HEIGHT / 4 };
    m_Direction = std::make_pair(-2.5f, 10);
}

BossMonster::BossMonster(const BossMonster& df)
{
	m_Id = df.m_Id;
	m_PowerType = df.m_PowerType;
	m_BulletRangeId = df.m_BulletRangeId;
	m_Bullets = df.m_Bullets;
	m_Position = df.m_Position;
	m_Direction = df.m_Direction;
	m_ShootFrequency = df.m_ShootFrequency;
}

BossMonster::BossMonster(BossMonster&& df) noexcept
{
	try
	{
		m_Id = df.m_Id;
		m_PowerType = df.m_PowerType;
		m_BulletRangeId = df.m_BulletRangeId;
		m_Bullets = df.m_Bullets;
		m_Position = df.m_Position;
		m_Direction = df.m_Direction;
		m_ShootFrequency = df.m_ShootFrequency;
	}
	catch (const std::exception&)
	{
		// @Silent
	}
}

void BossMonster::Initialize()
{
	// Nothing.
}

void BossMonster::Update()
{
	m_Position.first += m_Direction.first;
	m_Position.second += m_Direction.second;

	if (m_Position.second > SCREEN_HEIGHT - 100 || m_Position.second < 100)
		m_Direction.second *= -1;
	if (m_ShootFrequency == SHOOT_FREQUENCY)
	{
		m_ShootFrequency = 0;
		m_Bullets.push_back(std::make_shared<BulletBoss>(m_Position, std::make_pair(-20.0f, 0), 0.0f, m_BulletRangeId++));
	}
	m_ShootFrequency++;
}

void BossMonster::Destroy()
{
}

void BossMonster::SetPosition(const std::pair<float, float>& position)
{
	m_Position = position;
}

void BossMonster::SetBulletRangeId(const std::uint32_t& fromId)
{
	m_BulletRangeId = fromId;
}

void BossMonster::SetId(const std::uint32_t& id)
{
	m_Id = id;
}

void BossMonster::SetPowerType(const PowerType& power)
{
	m_PowerType = power;
}

void BossMonster::RemoveBullet(const std::size_t& id)
{
	const auto it = std::find_if(m_Bullets.begin(), m_Bullets.end(), [&id](const Shared<BulletBoss>& bullet)
	{
		return id == bullet->GetId();
	});

	if (it != m_Bullets.end())
		m_Bullets.erase(it);
}

const IMonster::PowerType& BossMonster::GetPowerType() const
{
	return m_PowerType;
}

const float& BossMonster::GetShootFrequency() const
{
	return SHOOT_FREQUENCY;
}

const std::pair<float, float>& BossMonster::GetPosition() const
{
	return m_Position;
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> BossMonster::GetBulletsPosition() const
{
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> positions;

	for (const auto &bullet: m_Bullets)
	{
		bullet->Update();
		auto pos = bullet->GetPosition();
		positions.emplace_back(std::make_pair(bullet->GetId(), pos));
	}

	return positions;
}

const std::pair<float, float> BossMonster::GetBulletPosition(const std::size_t& index) const
{
	if (index > m_Bullets.size())
		throw std::out_of_range("Index is out of range, cannot get bullet position.");

	return m_Bullets[index]->GetPosition();
}

std::size_t BossMonster::GetBullets() const
{
	return m_Bullets.size();
}

const std::string& BossMonster::GetFilename() const
{
	return m_Filename;
}

const std::string& BossMonster::GetBulletFilename() const
{
	return m_BulletFilename;
}

const std::size_t& BossMonster::GetId() const
{
	return m_Id;
}
