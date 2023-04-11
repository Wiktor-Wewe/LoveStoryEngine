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

bool Image::_loadSurface()
{
	this->_surface = SDL_LoadBMP(this->_path.c_str());
	if (this->_surface == NULL)
	{
		printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool Image::_loadTexture()
{
	this->_texture = SDL_CreateTextureFromSurface(this->_renderer, this->_surface);
	if (this->_texture == NULL)
	{
		printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool Image::getSurfaceStatus()
{
	return this->_surfaceStatus;
}

bool Image::getTextureStatus()
{
	return this->_textureStatus;
}