#pragma once

#include <Core.hpp>
#include <RType.Common.hpp>

class RTYPECOMMON_API ITask
{
public:
	virtual ~ITask() = default;

public:
	virtual void Execute() = 0;
};