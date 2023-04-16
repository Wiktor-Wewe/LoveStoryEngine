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
		this->_x = 0;
		this->_y = 0;
	}
	int getId();
	std::string getName();
	std::vector<int> getSprites();
	int getCurrentSprite();
	int getX();
	int getY();
	void setCurrentSprite(int id);
	void setX(int x);
	void setY(int y);

private:

	int _id;
	std::string _name;
	std::vector<int> _spritesId;
	int _currentSprite;
	int _x;
	int _y;
};