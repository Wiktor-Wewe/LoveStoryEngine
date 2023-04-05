#include "Sfx.h"

int Sfx::getId()
{
    return this->_id;
}

std::string Sfx::getName()
{
    return this->_name;
}

std::string Sfx::getPath()
{
    return this->_path;
}

bool Sfx::_loadSound()
{
    this->_sound = Mix_LoadWAV("nazwa_pliku.wav");
    if (this->_sound == NULL) {
        printf("Unable to load sound! SDL_Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}
