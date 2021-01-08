#pragma once

#include <Systems/System.hpp>
#include <Components/Monster.hpp>
#include <Managers/GameManager.hpp>

class RTYPECOMMON_API MonsterSystem final : public System<Monster>
{
public:
	explicit MonsterSystem(const std::size_t& id, Pointer<GameManager> gameManager);
	MonsterSystem(const MonsterSystem&) = default;
	MonsterSystem(MonsterSystem&&) noexcept = default;
	~MonsterSystem() override = default;

public:
	MonsterSystem& operator=(const MonsterSystem&) = delete;
	MonsterSystem& operator=(MonsterSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event & event) override;
	void OnPacket(const RType::RGamePack & pack) override;

private:
	void UpdateMonster(const uint32_t& monsterId, const std::pair<float, float>& position) const;
	void LoadBullets(const std::string& filename, const uint32_t& bulletId, const std::pair<float, float>& position) const;
	void UpdateBullets(const std::vector<std::pair<uint32_t, std::pair<float, float>>>&bullets) const;
	void Destroy(Pointer<Monster> monster) const;
	void Destroy(const size_t & id) const;
private:
	Pointer<GameManager> m_GameManager;
};