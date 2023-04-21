#pragma once
#include <SDL_render.h>
#include <vector>
#include "Image.h"
#include "Message.h"
class Scene
{
public:
	Scene(SDL_Renderer* renderer) {
		this->_renderer = renderer;
	}

	void draw();
	void addImage(Image* image, int x, int y);
	void addRawImage(Message::rawimage x);
	void clear();

private:
	SDL_Renderer* _renderer;
	std::vector<Image*> _images;
	std::vector<Message::rawimage> _rawimages;

	struct Positions {
		int x;
		int y;
	};
	std::vector<Positions> _positions;
	void _drawRawimage(Message::rawimage x);

};

