#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
class OptionWindows
{
public:
	OptionWindows(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* frame, SDL_Texture* selectedFrame) {
		this->_renderer = renderer;
		this->_font = font;
		this->_textFrameTexture = frame;
		this->_selectedFrame = selectedFrame;
		int selected = 0;

		this->_position = { 0, 0, 640, 480 };
		this->_texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->_position.w, this->_position.h);
	}

	bool make();
	void update();
	SDL_Texture* getTexture();
	int getSelectedId();
	void setSelect(int dy);
	void setTexts(std::vector<std::string> texts);
	
private:
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	std::vector<std::string> _texts;
	SDL_Texture* _texture;
	SDL_Rect _position;
	SDL_Rect _positionSrc;
	
	std::vector<SDL_Texture*> _textsTextures;
	std::vector<SDL_Rect*> _textsPositions;

	SDL_Texture* _textFrameTexture;
	std::vector<SDL_Rect*> _textsFramesPositions;

	SDL_Texture* _selectedFrame;
	int selected;
};

