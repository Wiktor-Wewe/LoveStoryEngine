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
	this->_surface = IMG_Load(this->_path.c_str());
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

void Image::draw(int x, int y)
{
	if (this->_surfaceStatus) {
		this->_dest_rect = { x, y, this->_surface->w, this->_surface->h };
		if (this->_textureStatus) {
			SDL_RenderCopy(this->_renderer, this->_texture, NULL, &this->_dest_rect);
		}
		else {
			std::cout << "Image id: " << std::to_string(this->_id);
			std::cout << " texture status: false" << std::endl;
		}
	}
	else {
		std::cout << "Image id: " << std::to_string(this->_id);
		std::cout << " surface status: false" << std::endl;
	}
}

SDL_Surface* Image::getSurface()
{
	return this->_surface;
}

SDL_Texture* Image::getTexture()
{
	return this->_texture;
}
