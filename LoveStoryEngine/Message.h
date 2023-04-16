#pragma once
#include <string>
#include <vector>
#include <SDL_ttf.h>
#include <iostream>

class Message
{
public:
	Message(int id, int characterId, std::string text, std::vector<int> musicId, std::vector<int> sfxId,
		int spriteId, int animationId, int clothesId, int bgImageId, int nextMessage, int nextEvent,
		int messageX, int messageY, int characterX, int characterY, std::vector<int> showCharacters, 
		SDL_Renderer* renderer, TTF_Font* font)
	{
		this->_id = id;
		this->_characterId = characterId;
		this->_text = text;
		this->_musicId = musicId;
		this->_sfxId = sfxId;
		this->_spriteId = spriteId;
		this->_animationId = animationId;
		this->_clothesId = clothesId;
		this->_bgImageId = bgImageId;
		this->_nextMessage = nextMessage;
		this->_nextEvent = nextEvent;
		this->_messageX = messageX;
		this->_messageY = messageY;
		this->_characterX = characterX;
		this->_characterY = characterY;
		this->_showCharacters = showCharacters;
		this->_renderer = renderer;
		this->_font = font;

		this->_surfaceStatus = this->_loadSurface();
		this->_textureStatus = false;
		if (this->_surfaceStatus) {
			this->_textureStatus = this->_loadTexture();
		}
	}
	int getId();
	int getCharacterId();
	std::string getText();
	std::vector<int> getAllMusicId();
	std::vector<int> getAllSfxId();
	int getSpriteId();
	int getAnimationId();
	int getClothesId();
	int getBgImageId();
	int getNextMessage();
	int getNextEvent();
	int getMessageX();
	int getMessageY();
	int getCharacterX();
	int getCharacterY();
	std::vector<int> getShowCharacters();
	bool getSurfaceStatus();
	bool getTextureStatus();
	void draw();

private:
	int _id;
	int _characterId; // 0 = none, 1 = protagonist, >1 = characters
	std::string _text;
	std::vector<int> _musicId;
	std::vector<int> _sfxId;
	int _spriteId;
	int _animationId;
	int _clothesId;
	int _bgImageId;
	int _nextMessage;
	int _nextEvent;
	int _messageX;
	int _messageY;
	int _characterX;
	int _characterY;
	std::vector<int> _showCharacters;

	// sdl
	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	TTF_Font* _font;
	SDL_Rect _dest_rect;
	bool _surfaceStatus;
	bool _textureStatus;

	bool _loadSurface();
	bool _loadTexture();
};

