#pragma once

#include <Core.hpp>
#include <RType.Common.hpp>
#include <Entities/IEntity.hpp>
#include <SFML/Window/Event.hpp>
#include <Models/RGamePack.pb.h>
class RTYPECOMMON_API ISystem
{

public:
	virtual ~ISystem() = default;

public:
	virtual void OnEntityCreated(const IEntity& e) = 0;
	virtual void OnEntityDestroyed(const std::size_t& id) = 0;
	virtual void Update(const double& deltaTime) = 0;
	virtual void OnEvent(sf::Event& event) = 0;
	virtual void OnPacket(const RType::RGamePack& pack) = 0;

public:
	[[nodiscard]] virtual const std::string& GetId() const = 0;
};