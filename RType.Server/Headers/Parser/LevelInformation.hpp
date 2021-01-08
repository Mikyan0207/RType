#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>
#include <Parser/PowerType.hpp>

struct LevelInformation
{
    std::string Monster;
    sf::Vector2f Position;
    float SpawnTime;
    PowerType Power;
};