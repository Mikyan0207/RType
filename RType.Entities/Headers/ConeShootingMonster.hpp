#pragma once
#include <Reloader/Interfaces/IMonster.hpp>
#include <RType.Entities.hpp>
#include <memory>
#include <algorithm>
#include <Bullet.hpp>
#include <string>

	class ConeShootingMonster final : public IMonster
{
public:
	ConeShootingMonster();
	ConeShootingMonster(const ConeShootingMonster&);
	ConeShootingMonster(ConeShootingMonster&&) noexcept;
	~ConeShootingMonster() override = default;

public:
	ConeShootingMonster& operator=(const ConeShootingMonster&) = delete;
	ConeShootingMonster& operator=(ConeShootingMonster&&) noexcept = delete;

public:
	void Initialize() override;
	void Update() override;
	void Destroy() override;
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> Shoot() override;

public:
	void SetPosition(const std::pair<float, float>& position) override;
	void SetBulletRangeId(const std::uint32_t& fromId) override;
	void SetId(const std::uint32_t& id) override;
	void SetPowerType(const PowerType& power) override;
	void RemoveBullet(const std::size_t& id) override;

public:
	[[nodiscard]] const std::size_t& GetId() const override;
	[[nodiscard]] const std::pair<float, float>& GetPosition() const override;
	[[nodiscard]] std::vector<std::pair<std::uint32_t, std::pair<float, float>>> GetBulletsPosition() const override;
	[[nodiscard]] const std::pair<float, float> GetBulletPosition(const std::size_t& index) const override;
	[[nodiscard]] std::size_t GetBullets() const override;
	[[nodiscard]] const std::string& GetFilename() const override;
	[[nodiscard]] const std::string& GetBulletFilename() const override;
	[[nodiscard]] const PowerType& GetPowerType() const override;
	[[nodiscard]] const float& GetShootFrequency() const override;
	[[nodiscard]] const std::pair<double, double>& GetScale() override;
	[[nodiscard]] const std::pair<double, double>& GetSize() override;
	[[nodiscard]] const std::pair<double, double>& GetAnimationFrameInfo() override;
	[[nodiscard]] const std::pair<double, double>& GetBulletScale() override;
	[[nodiscard]] const std::pair<double, double>& GetBulletSize() override;
	[[nodiscard]] const std::pair<double, double>& GetBulletAnimationInfo() override;

private:
	std::size_t m_Id;
	PowerType m_PowerType;
	std::string m_Filename;
	std::string m_BulletFilename;
	std::uint32_t m_BulletRangeId;
	std::vector<std::shared_ptr<Bullet>> m_Bullets;
	std::pair<float, float> m_Position;
	std::pair<float, float> m_Direction;
	std::uint16_t m_ShootFrequency;
	std::pair<double, double> m_Scale;
	std::pair<double, double> m_Size;
	std::pair<double, double> m_AnimationInfo;
	std::pair<double, double> m_BulletScale;
	std::pair<double, double> m_BulletSize;
	std::pair<double, double> m_BulletAnimationInfo;

private:
	static constexpr uint32_t SCREEN_WIDTH = 1600;
	static constexpr uint32_t SCREEN_HEIGHT = 900;
	static constexpr float SHOOT_FREQUENCY = 1.0f;
};

extern "C" RTYPEENTITIES_API IMonster * Instantiate(void)
{
	return new ConeShootingMonster;
}