#pragma once
#include <SDL_render.h>
#include <vector>
#include "Image.h"
#include "Message.h"
#include "Event.h"
class Scene
{
public:
	Scene(SDL_Renderer* renderer) {
		this->_renderer = renderer;
		this->_blackScene = false;
		this->_blackSceneImg = nullptr;
		this->windowShow = false;
		this->_set = 0;
	}

	void draw();
	void addImage(Image* image, int x, int y);
	void addRawImage(Message::rawimage x);
	void addRawImage(Event::rawimage x);
	void setSceneBlack(Image* image);
	void tryEraseImg(Image* image);
	void clear();

	void makeWindow(int x, int y, int w, int h, std::vector<std::vector<Image*>>& images);
	void changeSet(int x);
	bool isWindowShow();
	void scrolWindow(int dy);
	void clearWindow();
	void drawWindow();
	int getSelectedIdFromWindow(int x, int y);

	Image* getLastElementFromImage();

private:
	SDL_Renderer* _renderer;
	std::vector<Image*> _images;
	std::vector<Message::rawimage> _rawimages;
	std::vector<Event::rawimage> _rawimagesE;
	bool _blackScene;
	Image* _blackSceneImg;
	
	struct Positions {
		int x;
		int y;
	};
	std::vector<Positions> _positions;
	void _drawRawimage(Message::rawimage x);
	void _drawRawimage(Event::rawimage x);

	//window
	bool windowShow;
	SDL_Texture* _windowTexture;
	SDL_Texture* _windowSelTexture;
	SDL_Rect _windowSrc_rect;
	SDL_Rect _windowDest_rect;
	int _sizeOfTextureY;
	int _set;

	std::vector<std::vector<Image*>> _windowImages;
	std::vector<std::vector<Image*>> _listOfElements;
	std::vector<std::vector<int>> _idOfElemetsInOrder;

};

