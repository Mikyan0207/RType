#pragma once

#include <tuple>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

#include <Core.hpp>
#include <Entities/IEntity.hpp>
#include <Components/IComponent.hpp>
#include <Systems/ISystem.hpp>
#include <Exceptions/RTypeException.hpp>

template<class ... Components>
class System : public ISystem
{
public:
	explicit System(std::string id) : m_Id(std::move(id)) {}
	System(const System&) = default;
	System(System&&) noexcept = default;
	~System() override = default;

public:
	System& operator=(const System&) = default;
	System& operator=(System&&) noexcept = default;

protected:
	using CompTuple = std::tuple<Components*...>;

	const std::string m_Id;
	std::unordered_map<std::size_t, std::size_t> m_EntityIdToIndex;
	std::vector<CompTuple> m_Components;
	
public:
	void OnEntityCreated(const IEntity& e) final
	{
		CompTuple compTuple;
		std::size_t matchingComps = 0;

		//if (e.GetComponents().size() != sizeof...(Components))
		//	return;
		for (const auto &[id, component] : e.GetComponents())
		{
			if (ProcessEntityComponent<0, Components...>(id, component, compTuple))
			{
				matchingComps += 1;
			}
		}
		if (matchingComps == sizeof...(Components))
		{
			m_Components.emplace_back(std::move(compTuple));
			m_EntityIdToIndex.emplace(e.GetId(), m_Components.size() - 1);
		}
	}
	void OnEntityDestroyed(const std::size_t& id) final
	{
		const auto& it = m_EntityIdToIndex.find(id);

		if (it == m_EntityIdToIndex.end())
			return;

		m_Components[it->second] = std::move(m_Components.back());
		m_Components.pop_back();

		if (m_Components.empty() || m_Components.size() <= it->second)
			return;

		const auto movedComp = std::get<0>(m_Components[it->second]);
		const auto movedTupleIt = m_EntityIdToIndex.find(movedComp->GetEntityId());

		if (movedTupleIt == m_EntityIdToIndex.end())
			throw RTypeException(typeid(System).name(), "Error during Entity destruction.");

		movedTupleIt->second = it->second;
	}
	void Update(const double& deltaTime) override {}
	void OnEvent(sf::Event& event) override {}
	void OnPacket(const RType::RGamePack& pack) override {}

public:
	[[nodiscard]] const std::string& GetId() const final { return m_Id; }
	[[nodiscard]] const auto& GetComponents() const { return m_Components; }

private:
	template <size_t Index, class CompType, class ... CompArgs>
	bool ProcessEntityComponent(const std::size_t& id, IComponent* component, CompTuple& components)
	{
		if (CompType::Id == id)
		{
			std::get<Index>(components) = dynamic_cast<CompType*>(component);
			return true;
		}

		return ProcessEntityComponent<Index + 1, CompArgs...>(id, component, components);
	}

	template <size_t Index>
	static bool ProcessEntityComponent(const std::size_t& id, IComponent* component, CompTuple& components)
	{
		return false;
	}
};
