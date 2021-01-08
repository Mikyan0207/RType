#include <ServerScene.hpp>
#include <Entities/Entity.hpp>
#include <Systems/TransformSystem.hpp>
#include <Systems/MonsterSystem.hpp>
#include <Systems/CollisionSystem.hpp>
#include <Logger.hpp>

ServerScene::ServerScene(const std::size_t& id, const std::size_t& playerNb) : Scene(id)
{
	m_PlayerNumber = playerNb;
}

void ServerScene::OnCreate(Pointer<GameManager> gameManager)
{
	AddSystem(CreateUnique<TransformSystem>(1, gameManager));
	AddSystem(CreateUnique<MonsterSystem>(1, gameManager));
	AddSystem(CreateUnique<CollisionSystem>(1, gameManager));


	for (std::size_t i = 0; i < m_PlayerNumber; i += 1)
	{
		auto wrapper = RType::RGamePack();
		auto *content = new RType::LoadPacket();
		auto *vector2 = new RType::Vector2();

		wrapper.set_code(RType::RGamePack::LOAD);
		vector2->set_x(150);
		vector2->set_y(150 * (i + 1));
		content->set_id(static_cast<uint32_t>(i + 1));
		content->set_type(RType::LoadPacket::PLAYER);
		content->set_allocated_position(vector2);
		content->set_filename("Player_" + std::to_string(i) + ".png");
		wrapper.set_allocated_loadcontent(content);

		auto player = CreateUnique<Entity>(i + 1);
		auto *playerComponent = CreatePointer<Transform>(sf::Vector2f(150, 150));

		gameManager->GetUdpNetwork()->SendAsync(wrapper, i + 1);

		for (std::size_t j = 0; j < m_PlayerNumber; j += 1)
		{
			if (j == i)
				continue;

			auto wrapper2 = RType::RGamePack();
			auto content2 = new RType::LoadPacket();
			vector2 = new RType::Vector2();

			wrapper2.set_code(RType::RGamePack::LOAD);
			vector2->set_x(150);
			vector2->set_y(150 * j);
			content2->set_id(static_cast<uint32_t>(j + 1));
			content2->set_type(RType::LoadPacket::ALLY);
			content2->set_allocated_position(vector2);
			content2->set_filename("Player_" + std::to_string(j) + ".png");
			wrapper2.set_allocated_loadcontent(content2);

			gameManager->GetUdpNetwork()->SendAsync(wrapper2, i + 1);
		}

		player->AddComponent(playerComponent, Transform::Id);

		AddEntity(std::move(player));
	}
}
