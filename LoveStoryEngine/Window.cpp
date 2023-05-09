#include "Window.h"

void Window::_make()
{
	auto elementsOfSet = this->_elements[this->_set];

	int widthTexture = this->_windowRect.w;
	int heightTexture = this->_windowRect.h;
	int maxx = 0;
	int maxy = 0;

	maxx = this->_windowRect.w / elementsOfSet[0]->getSurface()->w;
	maxy = elementsOfSet.size() / maxx;
	if (elementsOfSet.size() % maxx != 0) {
		maxy++;
	}

	if (maxy * elementsOfSet[0]->getSurface()->h > this->_windowRect.h) {
		heightTexture = maxy * elementsOfSet[0]->getSurface()->h;
;	}

	this->_sizeOfTextureY = heightTexture;

	this->_texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, widthTexture, heightTexture);
	SDL_SetRenderTarget(this->_renderer, this->_texture);
	SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
	SDL_RenderClear(this->_renderer);

	this->_idInDrawOrder.push_back(std::vector<int>());
	int layer = 0;

	SDL_Rect buff_rect = { 0, 0, elementsOfSet[0]->getSurface()->w , elementsOfSet[0]->getSurface()->h };
	for (int i = 0; i < elementsOfSet.size(); i++) {
		SDL_RenderCopy(this->_renderer, elementsOfSet[i]->getTexture(), NULL, &buff_rect);
		this->_idInDrawOrder[layer].push_back(elementsOfSet[i]->getId());
		buff_rect.x += elementsOfSet[i]->getSurface()->w;
		if (buff_rect.x + buff_rect.w >= widthTexture) {
			buff_rect.x = 0;
			buff_rect.y += buff_rect.h;

			this->_idInDrawOrder.push_back(std::vector<int>());
			layer++;
		}
	}
	
	SDL_SetRenderTarget(this->_renderer, NULL);
	this->_windowRectToDraw = { 0, 0, widthTexture, this->_windowRect.h };
}

void Window::changeSet(int set)
{
	if (set > 0) {
		if (this->_set + set < this->_elements.size()) {
			this->_set += set;
		}
		else {
			this->_set = 0;
		}
	}
	else if (set < 0) {
		if (this->_set + set < 0) {
			this->_set = this->_elements.size() - 1;
		}
		else {
			this->_set += set;
		}
	}
}

bool Window::isWindowShow()
{
	return this->show;
}

void Window::setWindowStatus(bool status)
{
	this->show = status;
}

void Window::scroll(int dy)
{
	int maxh = this->_sizeOfTextureY - this->_windowRect.h;
	if (this->_windowRectToDraw.y + dy <= maxh && this->_windowRectToDraw.y + dy >= 0) {
		this->_windowRectToDraw.y += dy;
	}
}

void Window::clear()
{
	this->show = false;
	
	SDL_DestroyTexture(this->_texture);
	this->_texture = NULL;

	SDL_DestroyTexture(this->_textureWithSelect);
	this->_textureWithSelect = NULL;

	this->_sizeOfTextureY = 0;
	//this->_set = 0;

	this->_elements.clear();
	this->_idInDrawOrder.clear();
}

void Window::draw()
{
	SDL_RenderCopy(this->_renderer, this->_texture, &this->_windowRectToDraw, &this->_windowRect);
}

int Window::getSelectedIdFromImage(int mouseX, int mouseY)
{
	if (mouseX >= this->_windowRect.x && mouseX <= this->_windowRect.x + this->_windowRect.w &&
		mouseY >= this->_windowRect.y && mouseY <= this->_windowRect.y + this->_windowRect.h)
	{
		mouseX = mouseX - this->_windowRect.x;
		mouseY = mouseY - this->_windowRect.y;

		int sizeOfElemetnX = this->_elements[0][0]->getSurface()->w;
		int sizeOfElementY = this->_elements[0][0]->getSurface()->h;

		int elementX = mouseX / sizeOfElemetnX;
		int elementY = (mouseY + this->_windowRectToDraw.y) / sizeOfElementY;

		if (elementY >= 0 && elementY < this->_idInDrawOrder.size() &&
			elementX >= 0 && elementX < this->_idInDrawOrder[elementY].size())
		{
			return this->_idInDrawOrder[elementY][elementX];
		}
		return -1;
	}
	return 0;
}
