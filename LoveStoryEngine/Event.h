#pragma once
#include <vector>
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
class Event
{
public:
	Event(int id, std::vector<std::string> playerOptions, std::vector<int> nextMessages,
		std::vector<int> nextEvents, int mpei, int ccei, bool show, SDL_Renderer* renderer,
		TTF_Font* font)
	{
		this->_id = id;
		this->_playerOptions = playerOptions;
		this->_nextMessages = nextMessages;
		this->_nextEvents = nextEvents;
		this->_makeProtagonistEventId = mpei;
		this->_chooseClothesEventId = ccei;
		this->_show = show;
		this->_renderer = renderer;
		this->_font = font;

		if (this->_loadOptionsSurfaces()) {
			this->_loadOptionsTextures();
		}
	}
	int getId();
	std::vector<std::string> getPlayerOptions();
	std::vector<int> getNextMessages();
	std::vector<int> getNextEvents();
	int getMpei();
	int getCcei();
	bool isShowed();

	struct rawimage {
		SDL_Texture* texture;
		SDL_Rect* rect;
	};

	std::vector<Event::rawimage> getOptionsTextureRect();

private:
	int _id;
	std::vector<std::string> _playerOptions;
	std::vector<int> _nextMessages;
	std::vector<int> _nextEvents;
	int _makeProtagonistEventId;
	int _chooseClothesEventId;
	bool _show;

	// sdl
	SDL_Renderer* _renderer;
	std::vector<SDL_Surface*> _optionsSurfaces;
	std::vector<SDL_Texture*> _optionsTextures;

	TTF_Font* _font;

	bool _loadOptionsSurfaces();
	bool _loadOptionsTextures();
};

