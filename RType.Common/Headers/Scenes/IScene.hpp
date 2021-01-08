#pragma once

#include <Core.hpp>
#include <RType.Common.hpp>
#include <Managers/GameManager.hpp>
#include <Models/RGamePack.pb.h>

class GameManager;

class RTYPECOMMON_API IScene
{
public:
    virtual ~IScene() = default;

public:
    virtual void OnCreate(Pointer<GameManager> gameManager) = 0;
    virtual void OnDestroy() = 0;
    virtual void DispatchEvent(sf::Event& event) = 0;
	virtual void DispatchPacket(const RType::RGamePack& pack) = 0;
    virtual void Update(const double& delta) = 0;
	virtual void AddEntity(Unique<IEntity>&&) = 0;
    virtual void RemoveEntity(const std::size_t& id) = 0;

public:
    [[nodiscard]] virtual const std::size_t& GetId() const = 0;
    [[nodiscard]] virtual Pointer<IEntity> GetEntity(const std::size_t& id) = 0;
    [[nodiscard]] virtual const std::vector<Unique<IEntity>>& GetEntities() = 0;
};
