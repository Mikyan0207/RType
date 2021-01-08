#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <Parser/PowerType.hpp>
#include <Parser/LevelInformation.hpp>
#include <optional>

class Parser
{
    
public:
    Parser() = default;
    Parser(const Parser&) = default;
    Parser(Parser&&) noexcept = default;
    ~Parser() = default;

public:
    Parser& operator=(const Parser&) = default;
    Parser& operator=(Parser&&) noexcept = default;

public:
    void Parse(const std::string& file);

public:
    [[nodiscard]] const std::vector<LevelInformation>& GetInformation() const;
    [[nodiscard]] std::optional<LevelInformation> GetInformation(const float& spawnTime);
    [[nodiscard]] bool IsEmpty() const;
private:
    std::vector<LevelInformation> m_Information;
};