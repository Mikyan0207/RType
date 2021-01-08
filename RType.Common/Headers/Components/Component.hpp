#pragma once
#include <Components/IComponent.hpp>
#include <RType.Common.hpp>
#include <Scenes/Layouts.hpp>


class RTYPECOMMON_API Component : public IComponent
{
public:
	Component();
	Component(const Component&) = default;
	Component(Component&&) noexcept = default;
	~Component() override = default;

public:
	Component& operator=(const Component&) = default;
	Component& operator=(Component&&) noexcept = default;

public:
	void Destroy() override;

public:
	void SetEntityId(const std::size_t& id) final;

public:
	[[nodiscard]] const std::size_t& GetEntityId() const final;


protected:
	std::size_t m_EntityId;
	HorizontalLayout m_HorizontalLayout = HorizontalLayout::None;
	VerticalLayout m_VerticalLayout = VerticalLayout::None;
};