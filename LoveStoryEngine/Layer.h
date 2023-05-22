#pragma once
#include "Image.h"
#include <vector>
#include <SDL_ttf.h>

class Layer
{
public:
	Layer(SDL_Renderer* renderer) {
		this->_renderer = renderer;

		this->_position = { 0, 0, 640, 480 };
		this->_texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->_position.w, this->_position.h);
		SDL_SetTextureBlendMode(this->_texture, SDL_BLENDMODE_BLEND);
	}

	void draw();
	void make();
	void clear();
	
	bool addImage(Image* img, int x, int y);
	bool tryRemoveImg(Image* img);
	
	bool addText(std::string text, int x, int y, TTF_Font* font, int r, int g, int b, int a);
	bool tryRemoveText(int numberOfText);

	bool addTexture(SDL_Texture* texture, int x, int y, int w, int h, SDL_Rect* src = NULL);
	bool tryRemoveTexture(int numberOfTexture);

private:
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _position;

	std::vector<Image*> _images;
	std::vector<SDL_Rect*> _imagesPositions;

	std::vector<SDL_Texture*> _texts;
	std::vector<SDL_Rect*> _textsPositions;

	std::vector<SDL_Texture*> _textures;
	std::vector<SDL_Rect*> _texturesPositions;
	std::vector<SDL_Rect*> _texturesPositionsSrc;
};

