#pragma once
#include <vector>
#include "Image.h"
class Window
{
public:
	Window(int x, int y, int w, int h, std::vector<std::vector<Image*>>& elements, SDL_Renderer* renderer) {
		this->_windowRect = { x, h, w, h };

		this->_elements = elements;
		this->_renderer = renderer;

		this->_set = 0;
		this->_sizeOfTextureY = 0;
		this->show = true;

		this->_make();
	}

	void changeSet(int set);
	bool isWindowShow();
	void setWindowStatus(bool status);
	void scroll(int dy);
	void clear();
	void draw();
	int getSelectedIdFromImage(int mouseX, int mouseY);

private:
	int _set;
	int _sizeOfTextureY;

	bool show;

	std::vector<std::vector<Image*>> _elements;
	std::vector<std::vector<int>> _idInDrawOrder;

	void _make();

	//SDL
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Texture* _textureWithSelect;
	SDL_Rect _windowRect;
	SDL_Rect _windowRectToDraw;
};

