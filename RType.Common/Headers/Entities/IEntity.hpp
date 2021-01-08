#pragma once

#include <RType.Common.hpp>
#include <Components/IComponent.hpp>
#include <unordered_map>

class Entity;

class RTYPECOMMON_API IEntity
{
public:
	IEntity() = default;
	IEntity(const IEntity&) = default;
	IEntity(IEntity&&) noexcept = default;
	virtual ~IEntity() = default;

public:
	IEntity& operator=(const IEntity&) = default;
	IEntity& operator=(IEntity&&) noexcept = default;

public:
	virtual void Destroy() = 0;
	virtual Pointer<Entity> AsEntity() = 0;

public:
	[[nodiscard]] virtual const std::size_t& GetId() const = 0;
	[[nodiscard]] virtual const std::unordered_map<std::size_t, IComponent*, std::hash<std::size_t>, std::equal_to<>>& GetComponents() const = 0;
};
