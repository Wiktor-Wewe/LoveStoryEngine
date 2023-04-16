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

int Character::getCurrentSprite()
{
	return this->_spritesId[_currentSprite];
}

int Character::getX()
{
	return this->_x;
}

int Character::getY()
{
	return this->_y;
}

void Character::setCurrentSprite(int id)
{
	this->_currentSprite = id;
}

void Character::setX(int x)
{
	this->_x = x;
}

void Character::setY(int y)
{
	this->_y = y;
}
