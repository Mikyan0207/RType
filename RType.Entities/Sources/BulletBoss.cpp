#include <BulletBoss.hpp>

BulletBoss::BulletBoss(const std::pair<float, float> pos, const std::pair<float, float>&dir, const float gravityForce, std::uint32_t id): _id(id)
{
	_dir = dir;
	_gravityForce = gravityForce;
	_pos = pos;
}
void BulletBoss::Update()
{
	_dir.second -= _gravityForce;
	_pos.first += _dir.first;
	_pos.second += _dir.second;
}

const std::pair<float, float>& BulletBoss::GetPosition() const
{
	return _pos;
}
