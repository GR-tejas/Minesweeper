#include "../../header/Sound/SoundManager.h"
#include <iostream>

namespace Sound
{
    std::string SoundManager::button_click_path = "assets/sounds/button_click_sound.wav";
    std::string SoundManager::flag_sound_path = "assets/sounds/flag_sound.wav";
    std::string SoundManager::explosion_sound_path = "assets/sounds/explosion_sound.wav";
    std::string SoundManager::game_won_sound_path = "assets/sounds/game_won_sound.wav";
    std::string SoundManager::background_path = "assets/sounds/background_music.mp3";

    sf::Music SoundManager::backgroundMusic;
    sf::SoundBuffer SoundManager::bufferButtonClick;
    sf::SoundBuffer SoundManager::bufferFlagSound;
    sf::SoundBuffer SoundManager::bufferExplosion;
    sf::SoundBuffer SoundManager::bufferGameWon;
    sf::Sound SoundManager::soundEffect;

    float SoundManager::backgroundMusicVolume = 8.0f;

    void SoundManager::Initialize()
    {
        LoadBackgroundMusicFromFile();
        LoadSoundFromFile();
    }

    void SoundManager::LoadBackgroundMusicFromFile()
    {
        if (!backgroundMusic.openFromFile(background_path))
            std::cerr << "Error loading background music file: " << background_path << std::endl;
    }

    void SoundManager::LoadSoundFromFile()
    {
        if (!bufferButtonClick.loadFromFile(button_click_path))
            std::cerr << "Error loading sound file: " << button_click_path << std::endl;
        if (!bufferFlagSound.loadFromFile(flag_sound_path))
            std::cerr << "Error loading sound file: " << flag_sound_path << std::endl;
        if (!bufferExplosion.loadFromFile(explosion_sound_path))
            std::cerr << "Error loading sound file: " << explosion_sound_path << std::endl;
        if (!bufferGameWon.loadFromFile(game_won_sound_path))
            std::cerr << "Error loading sound file: " << game_won_sound_path << std::endl;
    }

    void SoundManager::PlaySound(SoundType soundType)
    {
        switch (soundType)
        {
        case SoundType::BUTTON_CLICK:
            soundEffect.setBuffer(bufferButtonClick);
            break;
        case SoundType::FLAG:
            soundEffect.setBuffer(bufferFlagSound);
            break;
        case SoundType::EXPLOSION:
            soundEffect.setBuffer(bufferExplosion);
            break;
        case SoundType::GAME_WON:
            soundEffect.setBuffer(bufferGameWon);
            break;
        default:
            std::cerr << "Invalid sound type" << std::endl;
            return;
        }

        soundEffect.play();
    }

    void SoundManager::PlayBackgroundMusic()
    {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(backgroundMusicVolume);
        backgroundMusic.play();
    }
}