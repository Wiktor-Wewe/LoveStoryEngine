#pragma once
#include "Image.h"
#include <vector>
#include <SDL_ttf.h>

class Layer
{
public:
	void draw();
	void make();
	
	bool addImage(Image* img, SDL_Rect& position);
	bool tryRemoveImg(Image* img);
	
	bool addTextTexture(std::string text, SDL_Rect& position, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	bool tryRemoveText(int numberOfText);

private:
	SDL_Texture* _texture;
	SDL_Rect _size;

	std::vector<Image*> _images;
	std::vector<SDL_Rect*> _imagesPositions;

	std::vector<SDL_Texture*> _texts;
	std::vector<SDL_Rect*> _textsPositions;
};

