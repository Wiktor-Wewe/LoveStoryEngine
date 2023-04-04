#include "ChooseClothesEvent.h"

int ChooseClothesEvent::getId()
{
    return this->_id;
}

std::string ChooseClothesEvent::getText()
{
    return this->_text;
}

std::vector<std::vector<int>> ChooseClothesEvent::getClothes()
{
    return this->_clothes;
}

int ChooseClothesEvent::getNextMessageId()
{
    return this->_nextMessageId;
}
