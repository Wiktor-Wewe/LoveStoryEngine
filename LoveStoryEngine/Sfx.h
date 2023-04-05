#pragma once
#include <string>
#include <SDL_mixer.h>

class Sfx
{
public:
	Sfx(int id, std::string name, std::string path)
	{
		this->_id = id;
		this->_name = name;
		this->_path = path;

		this->_soundStatus = this->_loadSound();
	}
	int getId();
	std::string getName();
	std::string getPath();

private:
	int _id;
	std::string _name;
	std::string _path;

	Mix_Chunk* _sound;
	bool _soundStatus;
	bool _loadSound();
};

