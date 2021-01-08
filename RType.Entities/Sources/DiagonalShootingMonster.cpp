#include <DiagonalShootingMonster.hpp>
#include <Bullet.hpp>
#include <stdexcept>

#include "Core.hpp"

DiagonalShootingMonster::DiagonalShootingMonster()
{
	m_Id = 230000 + std::rand() % 200000;
	m_PowerType = PowerType::None;
	m_BulletRangeId = m_Id + 1;
	m_Filename = "DiagonalShootingMonster.png";
	m_BulletFilename = "LinearShootingMonster_Bullet.png";
	m_ShootFrequency = 0;
	m_Position = { SCREEN_WIDTH + 100, SCREEN_HEIGHT / 4 };
	m_Direction = std::make_pair(-15.0f, -20.0f);

#pragma region Scale / Size / Animation - Monster
	m_Scale = { 1.0, 1.0 };
	m_Size = { 33, 34 };
	m_AnimationInfo = { 16, 0.3 };
#pragma endregion

#pragma region Scale / Size / Animation - Bullet
	m_BulletScale = { 2.0, 2.0 };
	m_BulletSize = { 16, 6 };
	m_BulletAnimationInfo = { 8, 0.5 };
#pragma endregion
}

 std::vector<std::pair<std::uint32_t, std::pair<float, float>>> DiagonalShootingMonster::Shoot()
{
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> tmp;
	m_Bullets.emplace_back(std::make_shared<Bullet>(m_Position, std::make_pair(-60.0f, 0), 0.0f, m_BulletRangeId++));
	tmp.emplace_back(std::make_pair(m_BulletRangeId, m_Position));

	return tmp;
}

DiagonalShootingMonster::DiagonalShootingMonster(const DiagonalShootingMonster& df)
{
	m_Id = df.m_Id;
	m_PowerType = df.m_PowerType;
	m_BulletRangeId = df.m_BulletRangeId;
	m_Bullets = df.m_Bullets;
	m_Position = df.m_Position;
	m_Direction = df.m_Direction;
	m_ShootFrequency = df.m_ShootFrequency;
}

DiagonalShootingMonster::DiagonalShootingMonster(DiagonalShootingMonster&& df) noexcept
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

void DiagonalShootingMonster::Initialize()
{
	// Nothing.
}

void DiagonalShootingMonster::Update()
{
	m_Position.first += m_Direction.first;
	m_Position.second += m_Direction.second;


	m_Bullets.erase(std::remove_if(m_Bullets.begin(), m_Bullets.end(), [](const std::shared_ptr<Bullet>& elem) { return elem->GetPosition().first < 0.0f; }), m_Bullets.end());
}

void DiagonalShootingMonster::Destroy()
{
}

void DiagonalShootingMonster::SetPosition(const std::pair<float, float>& position)
{
	m_Position = position;
}

void DiagonalShootingMonster::SetBulletRangeId(const std::uint32_t& fromId)
{
	m_BulletRangeId = fromId;
}

void DiagonalShootingMonster::SetId(const std::uint32_t& id)
{
	m_Id = id;
}

void DiagonalShootingMonster::SetPowerType(const PowerType& power)
{
	m_PowerType = power;
}

void DiagonalShootingMonster::RemoveBullet(const std::size_t& id)
{
	const auto it = std::find_if(m_Bullets.begin(), m_Bullets.end(), [&id](const Shared<Bullet>& bullet)
		{
			return id == bullet->GetId();
		});

	if (it != m_Bullets.end())
		m_Bullets.erase(it);
}

const IMonster::PowerType& DiagonalShootingMonster::GetPowerType() const
{
	return m_PowerType;
}

const float& DiagonalShootingMonster::GetShootFrequency() const
{
	return SHOOT_FREQUENCY;
}

const std::pair<double, double>& DiagonalShootingMonster::GetScale()
{
	return m_Scale;
}

const std::pair<double, double>& DiagonalShootingMonster::GetSize()
{
	return m_Size;
}

const std::pair<double, double>& DiagonalShootingMonster::GetAnimationFrameInfo()
{
	return m_AnimationInfo;
}

const std::pair<double, double>& DiagonalShootingMonster::GetBulletScale()
{
	return m_BulletScale;
}

const std::pair<double, double>& DiagonalShootingMonster::GetBulletSize()
{
	return m_BulletSize;
}

const std::pair<double, double>& DiagonalShootingMonster::GetBulletAnimationInfo()
{
	return m_BulletAnimationInfo;
}

const std::pair<float, float>& DiagonalShootingMonster::GetPosition() const
{
	return m_Position;
}

std::vector<std::pair<std::uint32_t, std::pair<float, float>>> DiagonalShootingMonster::GetBulletsPosition() const
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

const std::pair<float, float> DiagonalShootingMonster::GetBulletPosition(const std::size_t& index) const
{
	if (index > m_Bullets.size())
		throw std::out_of_range("Index is out of range, cannot get bullet position.");

	return m_Bullets[index]->GetPosition();
}

std::size_t DiagonalShootingMonster::GetBullets() const
{
	return m_Bullets.size();
}

const std::string& DiagonalShootingMonster::GetFilename() const
{
	return m_Filename;
}

const std::string& DiagonalShootingMonster::GetBulletFilename() const
{
	return m_BulletFilename;
}

const std::size_t& DiagonalShootingMonster::GetId() const
{
	return m_Id;
}
