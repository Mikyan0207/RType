#include <Entities/Entity.hpp>
#include <limits>

Entity::Entity() : m_Id(std::numeric_limits<std::size_t>::max())
{

}

Entity::Entity(const std::size_t& id) : m_Id(id)
{
}

Entity::Entity(const Entity& e)
{
	m_Id = e.m_Id;
	m_Components = e.m_Components;
}

Entity::Entity(const Entity&& e) noexcept
{
	try
	{
		m_Id = e.m_Id;
		m_Components = e.m_Components;
	}
	catch (...)
	{
		// @Silent
	}
}

const std::size_t& Entity::GetId() const
{
	return m_Id;
}

std::size_t Entity::GetSize() const
{
	return m_Components.size();
}

const std::unordered_map<std::size_t, IComponent*, std::hash<std::size_t>, std::equal_to<>>& Entity::GetComponents() const
{
	return m_Components;
}

Entity& Entity::operator=(const Entity& e)
{
	if (this == &e)
		return *this;

	m_Id = e.m_Id;
	m_Components = e.m_Components;

	return *this;
}

Entity& Entity::operator=(Entity&& e) noexcept
{
	if (this == &e)
		return *this;

	try
	{
		m_Id = e.m_Id;
		m_Components = e.m_Components;

		return *this;
	}
	catch (...)
	{
		// @Silent

		return *this;
	}
}

void Entity::Destroy()
{
	m_Components.clear();
}

void Entity::AddComponent(IComponent* component, const std::size_t& id)
{
	component->SetEntityId(m_Id);
	m_Components.emplace(id, component);
}
