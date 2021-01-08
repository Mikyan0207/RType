#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <Core.hpp>

class SoundManager
{
public:
    SoundManager() = default;
    SoundManager(const SoundManager&) = delete;
    SoundManager(SoundManager&&) noexcept;
    ~SoundManager() = default;

public:
	enum MusicType
	{
		MENU,
		GAME,
        SHOOT,
        KILL,
		DEATH
	};

public:
    SoundManager& operator=(const SoundManager&) = delete;
    SoundManager& operator=(SoundManager&&) noexcept = delete;

public:
    void LoadMusic(const MusicType& type, const std::string& filename);
    void PlayMusic(const MusicType& type, const float& volume = 20.0f);
    void StopMusic(const MusicType& type);

public:
    const bool IsMusicPlaying(const MusicType& type);

private:
    std::unordered_map<MusicType, Shared<sf::Music>> m_MusicMap;
};