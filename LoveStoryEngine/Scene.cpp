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

void Scene::tryEraseImg(Image* image)
{
	int position = -1;
	for (int i = 0; i < this->_images.size(); i++) {
		if (this->_images[i] == image) {
			position = i;
			this->_positions.erase(this->_positions.begin() + i);
		}
	}

	if (position >= 0) {
		this->_images.erase(this->_images.begin() + position);
	}
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

void Scene::makeWindow(int x, int y, int w, int h, std::vector<std::vector<Image*>>& images)
{
	this->_listOfElements = images;
	this->_windowDest_rect = { x, y, w, h };
	
	this->_windowImages = images;
	auto selColorimages = images[this->_set];

	int widthTexture = w;
	int heightTexture = h;
	int maxx = 0;
	int maxy = 0;

	maxx = w / selColorimages[0]->getSurface()->w;
	maxy = (selColorimages.size() / maxx);
	if (selColorimages.size() % maxx != 0) {
		maxy++;
	}

	if (maxy * selColorimages[0]->getSurface()->h > h) {
		heightTexture = maxy * selColorimages[0]->getSurface()->h;
	}

	this->_sizeOfTextureY = heightTexture;
	this->_windowTexture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, widthTexture, heightTexture);
	SDL_SetRenderTarget(this->_renderer, this->_windowTexture);
	SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
	SDL_RenderClear(this->_renderer);

	this->_idOfElemetsInOrder.push_back(std::vector<int>());
	int layer = 0;

	SDL_Rect buff_rect = { 0, 0, selColorimages[0]->getSurface()->w , selColorimages[0]->getSurface()->h };
	for (int i = 0; i < selColorimages.size(); i++) {
		SDL_RenderCopy(this->_renderer, selColorimages[i]->getTexture(), NULL, &buff_rect);
		this->_idOfElemetsInOrder[layer].push_back(selColorimages[i]->getId());
		buff_rect.x += selColorimages[i]->getSurface()->w;
		if (buff_rect.x + buff_rect.w >= widthTexture) {
			buff_rect.x = 0;
			buff_rect.y += buff_rect.h;

			this->_idOfElemetsInOrder.push_back(std::vector<int>());
			layer++;
		}
	}
	SDL_SetRenderTarget(this->_renderer, NULL);
	this->_windowSrc_rect = { 0, 0, widthTexture, h };
	this->windowShow = true;
}

void Scene::changeSet(int x)
{
	if (x > 0) {
		if (this->_set + x < this->_windowImages.size()) {
			this->_set += x;
		}
		else {
			this->_set = 0;
		}
	}
	else if (x < 0) {
		if (this->_set + x < 0) {
			this->_set = this->_windowImages.size() - 1;
		}
		else {
			this->_set += x;
		}
	}
}

bool Scene::isWindowShow()
{
	return this->windowShow;
}

void Scene::scrolWindow(int dy)
{
	int maxh = this->_sizeOfTextureY - this->_windowDest_rect.h;
	if (this->_windowSrc_rect.y + dy <= maxh && this->_windowSrc_rect.y + dy >= 0) {
		this->_windowSrc_rect.y += dy;
	}
}

void Scene::clearWindow()
{
	this->windowShow = false;
	
	SDL_DestroyTexture(this->_windowTexture);
	this->_windowTexture = NULL;

	SDL_DestroyTexture(this->_windowSelTexture);
	this->_windowSelTexture = NULL;

	this->_sizeOfTextureY = 0;
	//this->_set = 0;

	this->_windowImages.clear();
	this->_listOfElements.clear();
	this->_idOfElemetsInOrder.clear();
}

void Scene::drawWindow()
{
	SDL_RenderCopy(this->_renderer, this->_windowTexture, &this->_windowSrc_rect, &_windowDest_rect);
}

int Scene::getSelectedIdFromWindow(int x, int y)
{
	if (x >= this->_windowDest_rect.x && x <= this->_windowDest_rect.x + this->_windowDest_rect.w &&
		y >= this->_windowDest_rect.y && y <= this->_windowDest_rect.y + this->_windowDest_rect.h) 
	{
		x = x - this->_windowDest_rect.x;
		y = y - this->_windowDest_rect.y;

		int sizeOfElemetnX = this->_listOfElements[0][0]->getSurface()->w;
		int sizeOfElementY = this->_listOfElements[0][0]->getSurface()->h;

		int elementX = x / sizeOfElemetnX;
		int elementY = (y + this->_windowSrc_rect.y) / sizeOfElementY;

		if (elementY >= 0 && elementY < this->_idOfElemetsInOrder.size() && 
			elementX >= 0 && elementX < this->_idOfElemetsInOrder[elementY].size()) 
		{
			return this->_idOfElemetsInOrder[elementY][elementX];
		}
		return -1;
	}
	return 0;
}

Image* Scene::getLastElementFromImage()
{
	if (this->_images.empty()) {
		return nullptr;
	}

	return this->_images[this->_images.size() - 1];
}

void Scene::_drawRawimage(Message::rawimage x)
{
	SDL_RenderCopy(this->_renderer, x.texture, NULL, x.rect);
}

void Scene::_drawRawimage(Event::rawimage x)
{
	SDL_RenderCopy(this->_renderer, x.texture, NULL, x.rect);
}
