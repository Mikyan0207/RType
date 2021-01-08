#include <Components/Component.hpp>

Component::Component()
{
	m_EntityId = 0;
}

/// <summary>
/// Destroy component allocated resources.
/// </summary>

void Component::Destroy()
{
}

/// <summary>
/// Set the id of the entity to which the component is attached.
/// </summary>
/// <param name="id">Entity id.</param>
void Component::SetEntityId(const std::size_t& id)
{
	m_EntityId = id;
}

/// <summary>
/// Get the id of the entity to which the component is attached.
/// </summary>
/// <returns>Entity id.</returns>
const std::size_t& Component::GetEntityId() const
{
	return m_EntityId;
}
