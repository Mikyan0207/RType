#include <Scenes/Scene.hpp>

Scene::Scene(const std::size_t& id) : m_Id(id)
{
}

Scene::Scene(Scene&& other) noexcept : m_Id(other.m_Id), m_Entities(std::move(other.m_Entities)), m_Systems(std::move(other.m_Systems))
{
}

Scene& Scene::operator=(Scene&& other) noexcept
{
	try
	{
		m_Systems = std::move(other.m_Systems);
		m_Entities = std::move(other.m_Entities);

		return *this;
	}
	catch (...)
	{
		// @Silent
		return *this;
	}

}

void Scene::OnCreate(const Pointer<GameManager> gameManager)
{
}

void Scene::OnDestroy()
{
	m_Systems.clear();
	m_Entities.clear();
}

void Scene::DispatchEvent(sf::Event& event)
{
	for (auto&& system : m_Systems)
		system->OnEvent(event);
}

#include <Logger.hpp>
void Scene::DispatchPacket(const RType::RGamePack& pack)
{
	for (auto&& system : m_Systems)
	{
		system->OnPacket(pack);
	}
}

void Scene::Update(const double& delta)
{
	for (auto&& system : m_Systems)
		system->Update(delta);
}

void Scene::RemoveEntity(const std::size_t& id)
{
	const auto it = std::find_if(m_Entities.begin(), m_Entities.end(), [&id](const Unique<IEntity>& entity)
	{
		return entity->GetId() == id;
	});

	if (it == m_Entities.end())
		return;

	for (auto&& system : m_Systems)
	{
		if (*it != nullptr)
			system->OnEntityDestroyed((*it)->GetId()); // Σ(°△°|||)︴
	}

	m_Entities.erase(it);
}

Pointer<IEntity> Scene::GetEntity(const std::size_t& id)
{
	const auto it = std::find_if(m_Entities.begin(), m_Entities.end(), [&id](const Unique<IEntity>& entity)
	{
		return entity->GetId() == id;
	});

	if (it == m_Entities.end())
		return nullptr;

	return (*it).get(); // (￢_￢)

}

const std::vector<Unique<IEntity>>& Scene::GetEntities()
{
	return m_Entities;
}

void Scene::AddEntity(Unique<IEntity>&& entity)
{
	m_Entities.emplace_back(std::move(entity));

	for (auto && system : m_Systems)
	{
		system->OnEntityCreated(*m_Entities.back());
	}
}

void Scene::AddSystem(Unique<ISystem>&& system)
{
	m_Systems.emplace_back(std::move(system));

	for (auto && entity : m_Entities)
	{
		m_Systems.back()->OnEntityCreated(*entity);
	}
}

const std::size_t& Scene::GetId() const
{
	return m_Id;
}
