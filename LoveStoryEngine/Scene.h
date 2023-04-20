#pragma once
#include <SDL_render.h>
#include <vector>
#include "Image.h"
class Scene
{
public:
	Scene(SDL_Renderer* renderer) {
		this->_renderer = renderer;
	}

	void draw();
	void addImage(Image* image, int x, int y);
	void clear();

private:
	SDL_Renderer* _renderer;
	std::vector<Image*> _images;

	struct Positions {
		int x;
		int y;
	};
	std::vector<Positions> _positions;

};

