#include <Managers/SoundManager.hpp>
#include <iostream>

SoundManager::SoundManager(SoundManager&& other) noexcept
{
	for (auto && elem : other.m_MusicMap)
	{
        m_MusicMap.insert(std::move(elem));
	}
}

void SoundManager::LoadMusic(const MusicType& type, const std::string& filename)
{
    auto music = CreateShared<sf::Music>();
    if (!music->openFromFile(filename))
    {
        std::cerr << "Couldn't open music file." << std::endl;
    	return;
    }
    m_MusicMap.insert({ type, music });
}

void SoundManager::PlayMusic(const MusicType& type, const float& volume)
{
    auto music = std::find_if(
        m_MusicMap.begin(),
        m_MusicMap.end(),
        [type](const std::pair<MusicType, Shared<sf::Music>>& elem)
        {
            return type == elem.first;
        });
    if (music != m_MusicMap.end())
    {
        music->second->setPlayingOffset(sf::Time::Zero);
        music->second->setVolume(volume);
        music->second->play();
    }
}

void SoundManager::StopMusic(const MusicType& type)
{
    auto music = std::find_if(
        m_MusicMap.begin(),
        m_MusicMap.end(),
        [type](const std::pair<MusicType, Shared<sf::Music>>& elem)
        {
            return type == elem.first;
        });
    if (music != m_MusicMap.end())
    {
        music->second->stop();
    }
}

const bool SoundManager::IsMusicPlaying(const MusicType& type)
{
    auto music = std::find_if(
        m_MusicMap.begin(),
        m_MusicMap.end(),
        [type](const std::pair<MusicType, Shared<sf::Music>>& elem)
        {
            return type == elem.first;
        });
    if (music != m_MusicMap.end())
    {
        return (music->second->getStatus() == sf::SoundStream::Playing);
    }
    return false;
}
