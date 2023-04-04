#pragma once
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
class Music
{
public:
	Music(int id, std::string name, std::string path)
	{
		this->_id = id;
		this->_name = name;
		this->_path = path;

		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		this->_musicStatus = this->_loadMusic(path.c_str());
	}
	int getId();
	std::string getName();
	std::string getPath();

	bool getMusicStatus();
	void play();
	void stop();

private:
	int _id;
	std::string _name;
	std::string _path;

	Mix_Music* _music;
	bool _loadMusic(const char* filename);
	bool _musicStatus;
};

