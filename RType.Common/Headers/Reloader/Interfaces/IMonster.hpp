#pragma once
#include <cstddef>
#include <set>
#include <vector>
#include <string>
#include <cstdint>

#include <RType.Common.hpp>

class RTYPECOMMON_API IMonster
{
public:
	IMonster() = default;
	IMonster(const IMonster&) = default;
	IMonster(IMonster&&) noexcept = default;
	virtual ~IMonster() = default;

public:
	IMonster& operator=(const IMonster&) = default;
	IMonster& operator=(IMonster&&) noexcept = default;

public:
	enum class PowerType
	{
		None = 0,
		Speed,
		Damage,
		Shield
	};
	
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual std::vector<std::pair<std::uint32_t, std::pair<float, float>>> Shoot() = 0;
	virtual void Destroy() = 0;

public:
	virtual void SetPosition(const std::pair<float, float>& position) = 0;
	virtual void SetBulletRangeId(const std::uint32_t& fromId) = 0;
	virtual void SetId(const std::uint32_t& id) = 0;
	virtual void SetPowerType(const PowerType& power) = 0;
	virtual void RemoveBullet(const std::size_t& id) = 0;

public:
	[[nodiscard]] virtual const std::size_t& GetId() const = 0;
	[[nodiscard]] virtual const std::pair<float, float>& GetPosition() const = 0;
	[[nodiscard]] virtual std::vector<std::pair<std::uint32_t, std::pair<float, float>>> GetBulletsPosition() const = 0;
	[[nodiscard]] virtual const std::pair<float, float> GetBulletPosition(const std::size_t& index) const = 0;
	[[nodiscard]] virtual std::size_t GetBullets() const = 0;
	[[nodiscard]] virtual const std::string& GetFilename() const = 0;
	[[nodiscard]] virtual const std::string& GetBulletFilename() const = 0;
	[[nodiscard]] virtual const PowerType& GetPowerType() const = 0;
	[[nodiscard]] virtual const float& GetShootFrequency() const = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetScale() = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetSize() = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetAnimationFrameInfo() = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetBulletScale() = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetBulletSize() = 0;
	[[nodiscard]] virtual const std::pair<double, double>& GetBulletAnimationInfo() = 0;
};