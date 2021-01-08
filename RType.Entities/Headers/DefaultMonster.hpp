#pragma once
#include <Reloader/Interfaces/IMonster.hpp>
#include <RType.Entities.hpp>

class DefaultMonster final : public IMonster
{
public:
	DefaultMonster();
	DefaultMonster(const DefaultMonster&);
	DefaultMonster(DefaultMonster&&) noexcept;
	~DefaultMonster() override = default;

public:
	DefaultMonster& operator=(const DefaultMonster&) = delete;
	DefaultMonster& operator=(DefaultMonster&&) noexcept = delete;
	
public:
	void Initialize() override;
	void Update() override;
	void Destroy() override;

public:
	void SetPosition(const std::pair<float, float>& position) override;
	
public:
	[[nodiscard]] const std::size_t& GetId() const override;
	[[nodiscard]] const std::pair<float, float>& GetPosition() const override;
	[[nodiscard]] std::vector<std::pair<std::uint32_t, std::pair<float, float>>> GetBulletsPosition() const override;
	[[nodiscard]] const std::pair<float, float> GetBulletPosition(const std::size_t& index) const override;
	[[nodiscard]] std::size_t GetBullets() const override;

private:
	const std::size_t m_Id = 0x0001;
	std::vector<std::pair<std::uint32_t, std::pair<float, float>>> m_Bullets;
	std::pair<float, float> m_Position;
};

extern "C" inline RTYPEENTITIES_API IMonster* Instantiate(void)
{
	return new DefaultMonster;
}