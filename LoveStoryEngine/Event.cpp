#include "Event.h"

int Event::getId()
{
    return this->_id;
}

std::vector<std::string> Event::getPlayerOptions()
{
    return this->_playerOptions;
}

std::vector<int> Event::getNextMessages()
{
    return this->_nextMessages;
}

std::vector<int> Event::getNextEvents()
{
    return this->_nextEvents;
}

int Event::getMpei()
{
    return this->_makeProtagonistEventId;
}

int Event::getCcei()
{
    return this->_chooseClothesEventId;
}

bool Event::isShowed()
{
    return this->_show;
}

std::vector<Event::rawimage> Event::getOptionsTextureRect()
{
    std::vector<Event::rawimage> list;
    for (int i = 0; i < this->_optionsTextures.size(); i++) {
        SDL_Rect* rect = new SDL_Rect{ 640/2 - this->_optionsSurfaces[i]->w / 2, 150+(i*50), this->_optionsSurfaces[i]->w, this->_optionsSurfaces[i]->h};
        rawimage buff;
        buff.rect = rect;
        buff.texture = this->_optionsTextures[i];
        list.push_back(buff);
    }
    return list;
}

bool Event::_loadOptionsSurfaces()
{
    for (int i = 0; i < this->getPlayerOptions().size(); i++) {
        SDL_Surface* buff = TTF_RenderText_Solid(this->_font, this->getPlayerOptions()[i].c_str(), {255, 255, 255});
        if (buff == NULL) {
            printf("Unable to make option surface! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        this->_optionsSurfaces.push_back(buff);
    }
    return true;
}

bool Event::_loadOptionsTextures()
{
    for (int i = 0; i < this->getPlayerOptions().size(); i++) {
        SDL_Texture* buff = SDL_CreateTextureFromSurface(this->_renderer, this->_optionsSurfaces[i]);
        if (buff == NULL) {
            printf("Unable to make option texture! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        this->_optionsTextures.push_back(buff);
    }
    return true;
}
