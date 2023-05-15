#pragma once
#include <string>
#include <vector>
#include <SDL_ttf.h>
#include <iostream>

class Message
{
public:
	Message(int id, int characterId, std::string text, int musicId, std::vector<int> sfxId,
		int spriteId, int animationId, int clothesId, int bgImageId, int nextMessage, int nextEvent,
		int messageX, int messageY, int characterX, int characterY, std::vector<int> showCharacters, 
		SDL_Renderer* renderer, TTF_Font* font, std::string name)
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
		this->_name = name;

		this->_surfaceStatusName = this->_loadSurfaceName(name);
		this->_textureStatusName = false;
		if (this->_surfaceStatusName) {
			this->_textureStatusName = this->_loadTextureName();
		}

		this->_surfaceStatus = this->_loadSurface();
		this->_textureStatus = false;
		if (this->_surfaceStatus) {
			this->_textureStatus = this->_loadTexture();
		}
	}
	int getId();
	int getCharacterId();
	std::string getText();
	int getMusicId();
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
	std::string getName();

	struct rawimage {
		SDL_Texture* texture;
		SDL_Rect* rect;
	};

	rawimage getTextTexture();
	rawimage getNameTexture();

private:
	int _id;
	int _characterId; // 0 = none, 1 = protagonist, >1 = characters
	std::string _text;
	int _musicId;
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
	std::string _name;

	// sdl
	SDL_Renderer* _renderer;

	SDL_Surface* _surface;
	SDL_Surface* _surfaceName;
	
	SDL_Texture* _texture;
	SDL_Texture* _textureName;
	
	TTF_Font* _font;
	
	SDL_Rect _destRect;
	SDL_Rect _destRectName;
	
	bool _surfaceStatus;
	bool _surfaceStatusName;
	
	bool _textureStatus;
	bool _textureStatusName;

	bool _loadSurface();
	bool _loadSurfaceName(std::string name);

	bool _loadTexture();
	bool _loadTextureName();
};

