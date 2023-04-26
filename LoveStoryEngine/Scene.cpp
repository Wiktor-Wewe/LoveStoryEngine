#include "Scene.h"

void Scene::draw()
{
	for (int i = 0; i < this->_images.size(); i++) {
		this->_images[i]->draw(this->_positions[i].x, this->_positions[i].y);
	}
	for (int i = 0; i < this->_rawimages.size(); i++) {
		this->_drawRawimage(this->_rawimages[i]);
	}
	
	if (this->_blackScene) {
		this->_blackSceneImg->draw(0, 0);
	}

	for (int i = 0; i < this->_rawimagesE.size(); i++) {
 		this->_drawRawimage(this->_rawimagesE[i]);
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

void Scene::addRawImage(Event::rawimage x)
{
	this->_rawimagesE.push_back(x);
}

void Scene::setSceneBlack(Image* image)
{
	this->_blackScene = true;
	this->_blackSceneImg = image;
}

void Scene::clear()
{
	this->_images.clear();
	this->_positions.clear();
	this->_rawimages.clear();
	this->_rawimagesE.clear();
	this->_blackSceneImg = nullptr;
	this->_blackScene = false;
}

void Scene::_drawRawimage(Message::rawimage x)
{
	SDL_RenderCopy(this->_renderer, x.texture, NULL, x.rect);
}

void Scene::_drawRawimage(Event::rawimage x)
{
	SDL_RenderCopy(this->_renderer, x.texture, NULL, x.rect);
}
