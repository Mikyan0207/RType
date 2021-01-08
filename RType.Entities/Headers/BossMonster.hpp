#pragma once
#include <Reloader/Interfaces/IMonster.hpp>
#include <RType.Entities.hpp>
#include <memory>
#include <algorithm>
#include <BulletBoss.hpp>
#include <string>

class BossMonster final : public IMonster
{
public:
	BossMonster();
	BossMonster(const BossMonster&);
	BossMonster(BossMonster&&) noexcept;
	~BossMonster() override = default;

public:
	BossMonster& operator=(const BossMonster&) = delete;
	BossMonster& operator=(BossMonster&&) noexcept = delete;
	
public:
	void Initialize() override;
	void Update() override;
	void Destroy() override;

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

private:
	std::size_t m_Id;
	PowerType m_PowerType;
	std::string m_Filename;
	std::string m_BulletFilename;
	std::uint32_t m_BulletRangeId;
	std::vector<std::shared_ptr<BulletBoss>> m_Bullets;
	std::pair<float, float> m_Position;
    std::pair<float, float> m_Direction;
	std::uint16_t m_ShootFrequency;

private:
	static constexpr uint32_t SCREEN_WIDTH = 1600;
	static constexpr uint32_t SCREEN_HEIGHT = 900;
	static constexpr float SHOOT_FREQUENCY = 5.0f;
};

extern "C" RTYPEENTITIES_API IMonster * Instantiate(void)
{
	return new BossMonster;
}
