#pragma once
#include <string>
#include <SDL.h>

class Image
{
public:
	Image(int id, std::string name, std::string path, SDL_Renderer* renderer)
	{
		this->_id = id;
		this->_name = name;
		this->_path = path;
		this->_renderer = renderer;

		this->_surface = nullptr;
		this->_texture = nullptr;

		this->_surfaceStatus = this->_loadSurface();
		this->_textureStatus = false;
		if (this->_surfaceStatus) {
			this->_textureStatus = this->_loadTexture();
		}
	}
	int getId();
	std::string getName();
	std::string getPath();
	bool getSurfaceStatus();
	bool getTextureStatus();

private:
	int _id;
	std::string _name;
	std::string _path;

	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	bool _surfaceStatus;
	bool _textureStatus;

	bool _loadSurface();
	bool _loadTexture();
};

