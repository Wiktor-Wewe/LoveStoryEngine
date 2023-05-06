#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Image
{
public:
	Image(int id, std::string name, std::string path, SDL_Renderer* renderer)
	{
		this->_id = id; //500 - 600 reserved for base images
		this->_name = name;
		this->_path = path;
		this->_renderer = renderer;

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
	void draw(int x, int y);
	SDL_Surface* getSurface();
	SDL_Texture* getTexture();

private:
	int _id;
	std::string _name;
	std::string _path;

	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	SDL_Rect _dest_rect;
	bool _surfaceStatus;
	bool _textureStatus;

	bool _loadSurface();
	bool _loadTexture();
};

