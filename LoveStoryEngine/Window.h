#pragma once
#include <vector>
#include "Image.h"
class Window
{
public:
	Window(SDL_Renderer* renderer) {
		this->_renderer = renderer;

		this->_set = 0;
		this->_sizeOfTextureY = 0;
		this->_selectedX = 0;
		this->_selectedY = 0;
	}

	void setPosition(int x, int y, int w, int h);
	void setElements(std::vector<std::vector<Image*>>& elements);
	void setSelectFrame(SDL_Texture* frame);
	void make();
	void update();

	SDL_Texture* getTexture();
	SDL_Texture* getTextureWithSelect();
	SDL_Rect* getWindowRectToDraw();
	SDL_Rect* getWindowRect();

	void changeSet(int set);
	void scroll(int dy);
	void clear();
	void setCursor(int dx, int dy);
	int getSelectedIdFromImage(int mouseX, int mouseY);

private:
	int _set;
	int _sizeOfTextureY;
	int _selectedX;
	int _selectedY;

	std::vector<std::vector<Image*>> _elements;
	std::vector<std::vector<int>> _idInDrawOrder;
	std::vector<std::vector<SDL_Rect*>> _rectInDrawOrder;

	//SDL
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Texture* _textureWithSelect;
	SDL_Texture* _selectFrame;
	SDL_Rect _windowRect;
	SDL_Rect _windowRectToDraw;
};

