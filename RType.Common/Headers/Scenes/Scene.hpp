#pragma once

#include <vector>
#include <Scenes/IScene.hpp>
#include <Entities/IEntity.hpp>
#include <Systems/ISystem.hpp>

class RTYPECOMMON_API Scene : public IScene
{
public:
	explicit Scene(const std::size_t& id);
	Scene(const Scene&) = delete;
	Scene(Scene&& other) noexcept;
	~Scene() override = default;

public:
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) noexcept;

public:
	void OnCreate(Pointer<GameManager> gameManager) override;
	void OnDestroy() override;
	void DispatchEvent(sf::Event& event) override;
	void DispatchPacket(const RType::RGamePack& pack) override;
	void Update(const double& delta) override;
	void RemoveEntity(const std::size_t& id) override;

public:
	void AddEntity(Unique<IEntity>&& entity) override;
	void AddSystem(Unique<ISystem>&& system);

public:
	[[nodiscard]] const std::size_t& GetId() const override;
	[[nodiscard]] Pointer<IEntity> GetEntity(const std::size_t& id) override;
	[[nodiscard]] const std::vector<Unique<IEntity>>& GetEntities() override;
	
protected:
	const std::size_t m_Id;
	std::vector<Unique<IEntity>> m_Entities;
	std::vector<Unique<ISystem>> m_Systems;
};