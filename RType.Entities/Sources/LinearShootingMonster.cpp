#include <LinearShootingMonster.hpp>
#include <Bullet.hpp>
#include <stdexcept>

#include "Core.hpp"

LinearShootingMonster::LinearShootingMonster()
{
	m_Id = 460000 + std::rand() % 200000;
	m_PowerType = PowerType::None;
	m_BulletRangeId = m_Id + 1;
	m_Filename = "LinearShootingMonster.png";
	m_BulletFilename = "LinearShootingMonster_Bullet.png";
	m_ShootFrequency = 0;
	m_Position = { SCREEN_WIDTH + 100, SCREEN_HEIGHT / 4 };
    m_Direction = std::make_pair(-2.5f, 10);

#pragma region Scale / Size / Animation - Monster
	m_Scale = {2.0, 2.0};
	m_Size = { 30, 24 };
	m_AnimationInfo = { 4, 1 };
#pragma endregion

#pragma region Scale / Size / Animation - Bullet
	m_BulletScale = { 2.0, 2.0 };
	m_BulletSize = { 16, 6 };
	m_BulletAnimationInfo = { 8, 0.5 };
#pragma endregion
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> LinearShootingMonster::Shoot()
{
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> tmp;
	m_Bullets.push_back(std::make_shared<Bullet>(m_Position, std::make_pair(-20.0f, 0), 0.0f, m_BulletRangeId++));
	tmp.emplace_back(std::make_pair(m_BulletRangeId - 1, m_Position));

	return tmp;
}

LinearShootingMonster::LinearShootingMonster(const LinearShootingMonster& df)
{
	m_Id = df.m_Id;
	m_PowerType = df.m_PowerType;
	m_BulletRangeId = df.m_BulletRangeId;
	m_Bullets = df.m_Bullets;
	m_Position = df.m_Position;
	m_Direction = df.m_Direction;
	m_ShootFrequency = df.m_ShootFrequency;
}

LinearShootingMonster::LinearShootingMonster(LinearShootingMonster&& df) noexcept
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

void LinearShootingMonster::Initialize()
{
	// Nothing.
}

void LinearShootingMonster::Update()
{
	m_Position.first += m_Direction.first;
	m_Position.second += m_Direction.second;

	if (m_Position.second > SCREEN_HEIGHT - 100 || m_Position.second < 100)
		m_Direction.second *= -1;
}

void LinearShootingMonster::Destroy()
{
}

void LinearShootingMonster::SetPosition(const std::pair<float, float>& position)
{
	m_Position = position;
}

void LinearShootingMonster::SetBulletRangeId(const std::uint32_t& fromId)
{
	m_BulletRangeId = fromId;
}

void LinearShootingMonster::SetId(const std::uint32_t& id)
{
	m_Id = id;
}

void LinearShootingMonster::SetPowerType(const PowerType& power)
{
	m_PowerType = power;
}

void LinearShootingMonster::RemoveBullet(const std::size_t& id)
{
	const auto it = std::find_if(m_Bullets.begin(), m_Bullets.end(), [&id](const Shared<Bullet>& bullet)
	{
		return id == bullet->GetId();
	});

	if (it != m_Bullets.end())
		m_Bullets.erase(it);
}

const IMonster::PowerType& LinearShootingMonster::GetPowerType() const
{
	return m_PowerType;
}

const float& LinearShootingMonster::GetShootFrequency() const
{
	return SHOOT_FREQUENCY;
}

const std::pair<double, double>& LinearShootingMonster::GetScale()
{
	return m_Scale;
}

const std::pair<double, double>& LinearShootingMonster::GetSize()
{
	return m_Size;
}

const std::pair<double, double>& LinearShootingMonster::GetAnimationFrameInfo()
{
	return m_AnimationInfo;
}

const std::pair<double, double>& LinearShootingMonster::GetBulletScale()
{
	return m_BulletScale;
}

const std::pair<double, double>& LinearShootingMonster::GetBulletSize()
{
	return m_BulletSize;
}

const std::pair<double, double>& LinearShootingMonster::GetBulletAnimationInfo()
{
	return m_BulletAnimationInfo;
}

const std::pair<float, float>& LinearShootingMonster::GetPosition() const
{
	return m_Position;
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> LinearShootingMonster::GetBulletsPosition() const
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

const std::pair<float, float> LinearShootingMonster::GetBulletPosition(const std::size_t& index) const
{
	if (index > m_Bullets.size())
		throw std::out_of_range("Index is out of range, cannot get bullet position.");

	return m_Bullets[index]->GetPosition();
}

std::size_t LinearShootingMonster::GetBullets() const
{
	return m_Bullets.size();
}

const std::string& LinearShootingMonster::GetFilename() const
{
	return m_Filename;
}

const std::string& LinearShootingMonster::GetBulletFilename() const
{
	return m_BulletFilename;
}

const std::size_t& LinearShootingMonster::GetId() const
{
	return m_Id;
}
