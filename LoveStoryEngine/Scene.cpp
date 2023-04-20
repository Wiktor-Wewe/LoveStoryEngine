#include "Scene.h"

void Scene::draw()
{
	for (int i = 0; i < this->_images.size(); i++) {
		this->_images[i]->draw(this->_positions[i].x, this->_positions[i].y);
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

void Scene::clear()
{
	this->_images.clear();
	this->_positions.clear();
}

