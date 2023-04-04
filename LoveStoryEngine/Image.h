#pragma once
#include <string>
#include <SDL.h>

class Image
{
public:
	Image(int id, std::string name, std::string path)
	{
		this->_id = id;
		this->_name = name;
		this->_path = path;

		this->_image = NULL;
		this->_imgStatus = this->_loadImage();
	}
	int getId();
	std::string getName();
	std::string getPath();
	bool getImgStatus();

private:
	int _id;
	std::string _name;
	std::string _path;
	SDL_Surface* _image;
	bool _imgStatus;

	bool _loadImage();
};

