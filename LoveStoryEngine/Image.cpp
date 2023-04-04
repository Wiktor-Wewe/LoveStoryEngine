#include "Image.h"

int Image::getId()
{
    return this->_id;
}

std::string Image::getName()
{
    return this->_name;
}

std::string Image::getPath()
{
    return this->_path;
}

bool Image::_loadImage()
{
	this->_image = SDL_LoadBMP(this->_path.c_str());
	if (this->_image == NULL)
	{
		printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool Image::getImgStatus()
{
	return this->_imgStatus;
}