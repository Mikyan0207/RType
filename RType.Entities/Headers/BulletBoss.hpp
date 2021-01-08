#pragma once

#include <map>
#include <cstdint>

class BulletBoss
{
public:
	BulletBoss(const std::pair<float, float> pos, const std::pair<float, float> &dir, const float gravityForce, std::uint32_t id);

public:
	void Update();

public:
	[[nodiscard]] const std::pair<float, float>& GetPosition() const;
	[[nodiscard]] const std::uint32_t &GetId() const { return _id; }

private:
	const std::uint32_t _id;
	std::pair<float, float> _pos;
	std::pair <float, float> _dir;
	float _gravityForce;
};