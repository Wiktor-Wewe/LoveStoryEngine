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
