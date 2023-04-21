#include "Scene.h"

void Scene::draw()
{
	for (int i = 0; i < this->_images.size(); i++) {
		this->_images[i]->draw(this->_positions[i].x, this->_positions[i].y);
	}
	for (int i = 0; i < this->_rawimages.size(); i++) {
		this->_drawRawimage(this->_rawimages[i]);
	}
}

void Scene::addImage(Image* image, int x, int y)
{
	this->_images.push_back(image);
	Positions p;
	p.x = x;
	p.y = y;
	this->_positions.push_back(p);
}

void Scene::addRawImage(Message::rawimage x)
{
	this->_rawimages.push_back(x);
}

void Scene::clear()
{
	this->_images.clear();
	this->_positions.clear();
	this->_rawimages.clear();
}

void Scene::_drawRawimage(Message::rawimage x)
{
	SDL_RenderCopy(this->_renderer, x.texture, NULL, x.rect);
}

