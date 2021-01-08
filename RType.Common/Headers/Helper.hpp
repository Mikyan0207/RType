#pragma once

#include <RType.Common.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class RTYPECOMMON_API Helper
{
public:
    static std::string GetKeyAsString(const sf::Keyboard::Key& key);
};