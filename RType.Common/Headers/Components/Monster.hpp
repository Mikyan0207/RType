#pragma once

#include <Components/Component.hpp>
#include <Reloader/Interfaces/IMonster.hpp>
#include <SFML/System/Clock.hpp>
#include <optional>

class RTYPECOMMON_API Monster final : public Component
{
public:
	static constexpr std::size_t Id = 0x0008;

public:
	explicit Monster(const Shared<IMonster>& monster);
	Monster(const Monster&) = default;
	Monster(Monster&&) noexcept = default;

public:
	Monster& operator=(const Monster&) = default;
	Monster& operator=(Monster&&) noexcept = default;

public:
	void Destroy() override;
	std::optional<std::vector<std::pair<std::uint32_t, std::pair<float, float>>>> Shoot();

public:
	void SetShootFrequency(const double& shootFrequency);
	void SetLoaded(const bool& loaded);

public:
	[[nodiscard]] const Shared<IMonster>& GetIMonster() const;
	[[nodiscard]] const double& GetShootFrequency() const;
	[[nodiscard]] const bool& IsLoaded() const;

private:
	Shared<IMonster> m_Monster;
	bool Loaded = false;
	sf::Clock m_Clock;
};
