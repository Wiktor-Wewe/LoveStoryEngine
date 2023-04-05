#include "Music.h"

int Music::getId()
{
    return this->_id;
}

std::string Music::getName()
{
    return this->_name;
}

std::string Music::getPath()
{
    return this->_path;
}

bool Music::getMusicStatus()
{
    return this->_musicStatus;
}

void Music::play()
{
    Mix_PlayMusic(this->_music, -1);
}

void Music::stop()
{
    Mix_HaltMusic();
}

bool Music::_loadMusic(const char* filename)
{
    this->_music = Mix_LoadMUS(filename);
    if (this->_music == nullptr) {
        printf("Unable to load music! SDL_Error: %s\n", filename);
        return false;
    }
    return true;
}
