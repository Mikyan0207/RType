#pragma once
#include <cstddef>
#include <RType.Common.hpp>
#include <Core.hpp>

class RTYPECOMMON_API IComponent
{
public:
	virtual ~IComponent() = default;

public:
	virtual void Destroy() = 0;

public:
	virtual void SetEntityId(const std::size_t& id) = 0;
	
public:
	[[nodiscard]] virtual const std::size_t& GetEntityId() const = 0;
};