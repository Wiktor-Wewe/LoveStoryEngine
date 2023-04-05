#pragma once
#include <string>
#include <vector>

class Protagonist
{
public:
	Protagonist()
	{
		this->_name = "defaultName";
		this->_currentSpriteId = 0;
		
		this->_gSkins = std::vector<int>();
		this->_gFaces = std::vector<int>();
		this->_gHairs = std::vector<int>();
		this->_gClothes = std::vector<int>();
	}
	void setName(std::string name);
	void setGSkins(std::vector<int> gskins);
	void setGFaces(std::vector<int> gfaces);
	void setGHairs(std::vector<int> ghairs);
	void setGClothes(std::vector<int> glothes);
	void setSpriteId(int id);

	std::string getName();
	std::vector<int> getGSkins();
	std::vector<int> getGFaces();
	std::vector<int> getGHairs();
	std::vector<int> getGClothes();
	int getCurrentSpriteId();

	void printInfoAboutPlayer();

private:
	std::string _name;

	std::vector<int> _gSkins;
	std::vector<int> _gFaces;
	std::vector<int> _gClothes;
	std::vector<int> _gHairs;
	int _currentSpriteId;
};

