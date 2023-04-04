#pragma once
#include <string>
#include <vector>

class Character
{
public:
	Character(int id, std::string name, std::vector<int> spritesId)
	{
		this->_id = id;
		this->_name = name;
		this->_spritesId = spritesId;
		this->_currentSprite = 0;
	}
	int getId();
	std::string getName();
	std::vector<int> getSprites();


private:

	int _id;
	std::string _name;
	std::vector<int> _spritesId;
	int _currentSprite;
};