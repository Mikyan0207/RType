#include <Parser/Parser.hpp>
#include <filesystem>
#include <algorithm>

void Parser::Parse(const std::string& file)
{
	std::string line;
	std::ifstream reader(file);

	if (!reader.is_open())
		return;

	auto data = std::vector<std::string>();
	std::size_t pos = 0;

	data.reserve(5);
	while (std::getline(reader, line))
	{
		while ((pos = line.find(' ')) != std::string::npos) {
			data.emplace_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		data.emplace_back(line);

		m_Information.emplace_back(LevelInformation {
			data[0],
			sf::Vector2f(std::stof(data[1]), std::stof(data[2])),
			std::stof(data[3]),
			static_cast<PowerType>(std::stoi(data[4]))
		});

		data.clear();
	}
}

const std::vector<LevelInformation>& Parser::GetInformation() const
{
	return m_Information;
}

std::optional<LevelInformation> Parser::GetInformation(const float& spawnTime)
{
	const auto it = std::find_if(m_Information.begin(), m_Information.end(), [&spawnTime](const LevelInformation& info)
	{
		return info.SpawnTime <= spawnTime;
	});

	if (it == m_Information.end())
		return {};

	auto res = *it;
	m_Information.erase(it);
	
	return std::move(res);
}

bool Parser::IsEmpty() const
{
	return m_Information.empty();
}
