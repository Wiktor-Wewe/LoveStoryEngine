#include "Window.h"

void Window::make()
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
	this->_textureWithSelect = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, widthTexture, heightTexture);
	SDL_SetRenderTarget(this->_renderer, this->_texture);
	SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
	SDL_RenderClear(this->_renderer);

	this->_idInDrawOrder.push_back(std::vector<int>());
	this->_rectInDrawOrder.push_back(std::vector<SDL_Rect*>());
	int layer = 0;

	SDL_Rect buff_rect = { 0, 0, elementsOfSet[0]->getSurface()->w , elementsOfSet[0]->getSurface()->h };
	for (int i = 0; i < elementsOfSet.size(); i++) {
		SDL_RenderCopy(this->_renderer, elementsOfSet[i]->getTexture(), NULL, &buff_rect);
		this->_idInDrawOrder[layer].push_back(elementsOfSet[i]->getId());
		SDL_Rect* buff_rect_pointer = new SDL_Rect{ buff_rect.x, buff_rect.y, buff_rect.w, buff_rect.h };
		this->_rectInDrawOrder[layer].push_back(buff_rect_pointer);
		buff_rect.x += elementsOfSet[i]->getSurface()->w;
		if (buff_rect.x + buff_rect.w >= widthTexture) {
			buff_rect.x = 0;
			buff_rect.y += buff_rect.h;

			this->_idInDrawOrder.push_back(std::vector<int>());
			this->_rectInDrawOrder.push_back(std::vector<SDL_Rect*>());
			layer++;
		}
	}
	
	this->_windowRectToDraw = { 0, 0, widthTexture, this->_windowRect.h };
	this->update();
}

void Window::update()
{
	SDL_SetRenderTarget(this->_renderer, this->_textureWithSelect);
	SDL_RenderClear(this->_renderer);
	SDL_RenderCopy(this->_renderer, this->_texture, NULL, NULL);
	SDL_RenderCopy(this->_renderer, this->_selectFrame, NULL, this->_rectInDrawOrder[this->_selectedY][this->_selectedX]);
	SDL_SetRenderTarget(this->_renderer, NULL);
}

SDL_Texture* Window::getTexture()
{
	return this->_texture;
}

SDL_Texture* Window::getTextureWithSelect()
{
	return this->_textureWithSelect;
}

SDL_Rect* Window::getWindowRectToDraw()
{
	return &this->_windowRectToDraw;
}

SDL_Rect* Window::getWindowRect()
{
	return &this->_windowRect;
}

void Window::setPosition(int x, int y, int w, int h)
{
	this->_windowRect = { x, y, w, h };
}

void Window::setElements(std::vector<std::vector<Image*>>& elements)
{
	this->_elements = elements;
}

void Window::setSelectFrame(SDL_Texture* frame)
{
	this->_selectFrame = frame;
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

void Window::scroll(int dy)
{
	int maxh = this->_sizeOfTextureY - this->_windowRect.h;
	if (this->_windowRectToDraw.y + dy <= maxh && this->_windowRectToDraw.y + dy >= 0) {
		this->_windowRectToDraw.y += dy;
	}
}

void Window::clear()
{	
	SDL_DestroyTexture(this->_texture);
	this->_texture = NULL;

	SDL_DestroyTexture(this->_textureWithSelect);
	this->_textureWithSelect = NULL;

	this->_sizeOfTextureY = 0;
	//this->_set = 0;

	this->_elements.clear();
	this->_idInDrawOrder.clear();
}

void Window::setCursor(int dx, int dy)
{
	if (this->_selectedY + dy < 0) {
		this->_selectedY = this->_idInDrawOrder.size() -1 - (dx * -1);
		if (this->_idInDrawOrder[this->_selectedY].size() -1 < this->_selectedX) {
			this->_selectedX = this->_idInDrawOrder[this->_selectedY].size() - 1;
		}
	}
	else if (this->_selectedX + dx < 0) {
		this->_selectedX = this->_idInDrawOrder[this->_selectedY].size() -1 - (dy * -1);
	}
	else {
		this->_selectedY = (this->_selectedY + dy) % this->_idInDrawOrder.size();
		this->_selectedX = (this->_selectedX + dx) % this->_idInDrawOrder[this->_selectedY].size();
	}
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

int Window::getSelectedId()
{
	return this->_idInDrawOrder[this->_selectedY][this->_selectedX];
}
