#pragma once

#include <Systems/System.hpp>
#include <Components/Sprite.hpp>

class RTYPECOMMON_API SpriteSystem final : public System<Sprite>
{
public:
	explicit SpriteSystem(const std::size_t& id);
	SpriteSystem(const SpriteSystem&) = default;
	SpriteSystem(SpriteSystem&&) noexcept = default;
	~SpriteSystem() override = default;

public:
	SpriteSystem& operator=(const SpriteSystem&) = delete;
	SpriteSystem& operator=(SpriteSystem&&) noexcept = delete;

public:
	void Update(const double& deltaTime) override;
	void OnEvent(sf::Event& event) override;
	void OnPacket(const RType::RGamePack& pack) override;
};