#include "Protagonist.h"
#include <iostream>

void Protagonist::setName(std::string name)
{
	this->_name = name;
}

void Protagonist::setGSkins(std::vector<int> gskins)
{
	this->_gSkins = gskins;
}

void Protagonist::setGFaces(std::vector<int> gfaces)
{
	this->_gFaces = gfaces;
}

void Protagonist::setGHairs(std::vector<int> ghairs)
{
	this->_gHairs = ghairs;
}

void Protagonist::setGClothes(std::vector<int> glothes)
{
	this->_gClothes = glothes;
}

void Protagonist::setSpriteId(int id)
{
	this->_currentSpriteId = id;
}

std::string Protagonist::getName()
{
	return this->_name;
}

std::vector<int> Protagonist::getGSkins()
{
	return this->_gSkins;
}

std::vector<int> Protagonist::getGFaces()
{
	return this->_gFaces;
}

std::vector<int> Protagonist::getGHairs()
{
	return this->_gHairs;
}

std::vector<int> Protagonist::getGClothes()
{
	return this->_gClothes;
}

int Protagonist::getCurrentSpriteId()
{
	return this->_currentSpriteId;
}
