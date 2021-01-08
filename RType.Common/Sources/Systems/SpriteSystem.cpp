#include <Systems/SpriteSystem.hpp>

SpriteSystem::SpriteSystem(const std::size_t& id) : System<Sprite>("SpriteSystem#" + std::to_string(id))
{
}

void SpriteSystem::Update(const double& deltaTime)
{
}

void SpriteSystem::OnEvent(sf::Event& event)
{
	// TODO: ?
}

void SpriteSystem::OnPacket(const RType::RGamePack& pack)
{
	// TODO: Handle Packet for Sprites
	// TODO: Add tags for sprites (Monster/Player/Object)
	// Transform / Destroy / ...
}
