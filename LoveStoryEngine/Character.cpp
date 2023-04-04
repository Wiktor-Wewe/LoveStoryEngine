#include "Character.h"

int Character::getId()
{
	return this->_id;
}

std::string Character::getName()
{
	return this->_name;
}

std::vector<int> Character::getSprites()
{
	return this->_spritesId;
}
