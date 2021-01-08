#include <ConeShootingMonster.hpp>
#include <Bullet.hpp>
#include <stdexcept>

#include "Core.hpp"

ConeShootingMonster::ConeShootingMonster()
{
	m_Id = 10000 + std::rand() % 200000;
	m_PowerType = PowerType::None;
	m_BulletRangeId = m_Id + 1;
	m_Filename = "ConeShootingMonster.png";
	m_BulletFilename = "LinearShootingMonster_Bullet.png";
	m_ShootFrequency = 0;
	m_Position = { SCREEN_WIDTH + 100, SCREEN_HEIGHT / 4 };
	m_Direction = std::make_pair(-10.0f, 0);

#pragma region Scale / Size / Animation - Monster
	m_Scale = { 1.3, 1.3 };
	m_Size = { 33, 33 };
	m_AnimationInfo = { 3, 0.4 };
#pragma endregion

#pragma region Scale / Size / Animation - Bullet
	m_BulletScale = { 2.0, 2.0 };
	m_BulletSize = { 16, 6 };
	m_BulletAnimationInfo = { 8, 0.5 };
#pragma endregion
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> ConeShootingMonster::Shoot()
{
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> tmp;
	m_Bullets.push_back(std::make_shared<Bullet>(m_Position, std::make_pair(-45.0f, 15), 0.0f, m_BulletRangeId++));
	tmp.emplace_back(std::make_pair(m_BulletRangeId - 1, m_Position));
	m_Bullets.push_back(std::make_shared<Bullet>(m_Position, std::make_pair(-30.0f, 0), 0.0f, m_BulletRangeId++));
	tmp.emplace_back(std::make_pair(m_BulletRangeId - 1, m_Position));
	m_Bullets.push_back(std::make_shared<Bullet>(m_Position, std::make_pair(-45.0f, -15), 0.0f, m_BulletRangeId++));
	tmp.emplace_back(std::make_pair(m_BulletRangeId - 1, m_Position));

	return tmp;
}

ConeShootingMonster::ConeShootingMonster(const ConeShootingMonster& df)
{
	m_Id = df.m_Id;
	m_PowerType = df.m_PowerType;
	m_BulletRangeId = df.m_BulletRangeId;
	m_Bullets = df.m_Bullets;
	m_Position = df.m_Position;
	m_Direction = df.m_Direction;
	m_ShootFrequency = df.m_ShootFrequency;
}

ConeShootingMonster::ConeShootingMonster(ConeShootingMonster&& df) noexcept
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

void ConeShootingMonster::Initialize()
{
	// Nothing.
}

void ConeShootingMonster::Update()
{
	m_Position.first += m_Direction.first;
	m_Position.second += m_Direction.second;

	m_Bullets.erase(std::remove_if(m_Bullets.begin(), m_Bullets.end(), [](const std::shared_ptr<Bullet>& elem) { return elem->GetPosition().first < 0.0f; }), m_Bullets.end());
}

void ConeShootingMonster::Destroy()
{
}

void ConeShootingMonster::SetPosition(const std::pair<float, float>& position)
{
	m_Position = position;
}

void ConeShootingMonster::SetBulletRangeId(const std::uint32_t& fromId)
{
	m_BulletRangeId = fromId;
}

void ConeShootingMonster::SetId(const std::uint32_t& id)
{
	m_Id = id;
}

void ConeShootingMonster::SetPowerType(const PowerType& power)
{
	m_PowerType = power;
}

void ConeShootingMonster::RemoveBullet(const std::size_t& id)
{
	const auto it = std::find_if(m_Bullets.begin(), m_Bullets.end(), [&id](const Shared<Bullet>& bullet)
		{
			return id == bullet->GetId();
		});

	if (it != m_Bullets.end())
		m_Bullets.erase(it);
}


const IMonster::PowerType& ConeShootingMonster::GetPowerType() const
{
	return m_PowerType;
}

const float& ConeShootingMonster::GetShootFrequency() const
{
	return SHOOT_FREQUENCY;
}

const std::pair<double, double>& ConeShootingMonster::GetScale()
{
	return m_Scale;
}

const std::pair<double, double>& ConeShootingMonster::GetSize()
{
	return m_Size;
}

const std::pair<double, double>& ConeShootingMonster::GetAnimationFrameInfo()
{
	return m_AnimationInfo;
}

const std::pair<double, double>& ConeShootingMonster::GetBulletScale()
{
	return m_BulletScale;
}

const std::pair<double, double>& ConeShootingMonster::GetBulletSize()
{
	return m_BulletSize;
}

const std::pair<double, double>& ConeShootingMonster::GetBulletAnimationInfo()
{
	return m_BulletAnimationInfo;
}

const std::pair<float, float>& ConeShootingMonster::GetPosition() const
{
	return m_Position;
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> ConeShootingMonster::GetBulletsPosition() const
{
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> positions;

	for (const auto& bullet : m_Bullets)
	{
		bullet->Update();
		auto pos = bullet->GetPosition();
		if (pos.first < 0)
		{
			continue;
		}
		positions.emplace_back(std::make_pair(bullet->GetId(), pos));
	}

	return positions;
}

const std::pair<float, float> ConeShootingMonster::GetBulletPosition(const std::size_t& index) const
{
	if (index > m_Bullets.size())
		throw std::out_of_range("Index is out of range, cannot get bullet position.");

	return m_Bullets[index]->GetPosition();
}

std::size_t ConeShootingMonster::GetBullets() const
{
	return m_Bullets.size();
}

const std::string& ConeShootingMonster::GetFilename() const
{
	return m_Filename;
}

const std::string& ConeShootingMonster::GetBulletFilename() const
{
	return m_BulletFilename;
}

const std::size_t& ConeShootingMonster::GetId() const
{
	return m_Id;
}
