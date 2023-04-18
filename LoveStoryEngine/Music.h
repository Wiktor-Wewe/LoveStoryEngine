#pragma once
#include <string>
#include <SDL_mixer.h>
class Music
{
public:
	Music(int id, std::string name, std::string path)
	{
		this->_id = id;
		this->_name = name;
		this->_path = path;

		this->_musicStatus = this->_loadMusic(path.c_str());
		this->_isPlaying = false;
	}
	int getId();
	std::string getName();
	std::string getPath();

	bool getMusicStatus();
	bool isPlaying();
	void play();
	void stop();

private:
	int _id;
	std::string _name;
	std::string _path;

	Mix_Music* _music;
	bool _loadMusic(const char* filename);
	bool _musicStatus;
	bool _isPlaying;
};

