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
		SDL_SetRenderTarget(this->_renderer, this->_texture);
		SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
		SDL_RenderClear(this->_renderer);
		SDL_SetRenderTarget(this->_renderer, NULL);
	}

	void draw();
	void make();
	void clear();
	
	bool addImage(Image* img, SDL_Rect& position);
	bool tryRemoveImg(Image* img);
	
	bool addTextTexture(std::string text, SDL_Rect& position, TTF_Font* font, SDL_Color color);
	bool tryRemoveText(int numberOfText);

private:
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _position;

	std::vector<Image*> _images;
	std::vector<SDL_Rect*> _imagesPositions;

	std::vector<SDL_Texture*> _texts;
	std::vector<SDL_Rect*> _textsPositions;
};

