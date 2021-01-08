#pragma once
#include <cstddef>
#include <unordered_map>
#include <type_traits>
#include <optional>
#include <memory>

#include <RType.Common.hpp>
#include <Core.hpp>
#include <Entities/IEntity.hpp>
#include <Components/IComponent.hpp>

class RTYPECOMMON_API Entity final : public IEntity
{
public:
	[[deprecated("Use Entity::Entity(const std::size_t& id) instead.")]]
	Entity();
	explicit Entity(const std::size_t& id);
	~Entity() override = default;

public:
	Entity(const Entity&);
	Entity(const Entity&&) noexcept;

public:
	Entity& operator=(const Entity&);
	Entity& operator=(Entity&&) noexcept;

public:
	void Destroy() override;
	Pointer<Entity> AsEntity() override
	{
		return this;
	}

public:
	void AddComponent(IComponent* component, const std::size_t& id);

	template<typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	void RemoveComponent()
	{
		auto it = m_Components.find(T::Id);

		if (it == m_Components.end())
			return;

		m_Components.erase(it);
	}

public:
	[[nodiscard]] const std::size_t& GetId() const override;
	[[nodiscard]] std::size_t GetSize() const;
	[[nodiscard]] const std::unordered_map<std::size_t, IComponent*, std::hash<std::size_t>, std::equal_to<>>& GetComponents() const final;

	template<typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	std::optional<T*> GetComponent() const
	{
		auto it = m_Components.find(T::Id);

		if (it == m_Components.end())
			return {};

		return dynamic_cast<T*>(it->second);
	}

private:
	std::size_t m_Id;
	std::unordered_map<std::size_t, IComponent*, std::hash<std::size_t>, std::equal_to<>> m_Components;
};
