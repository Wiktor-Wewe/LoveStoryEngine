#include "Message.h"

int Message::getId()
{
	return this->_id;
}

int Message::getCharacterId()
{
	return this->_characterId;
}

std::string Message::getText()
{
	return this->_text;
}

std::vector<int> Message::getAllMusicId()
{
	return this->_musicId;
}

std::vector<int> Message::getAllSfxId()
{
	return this->_sfxId;
}

int Message::getSpriteId()
{
	return this->_spriteId;
}

int Message::getAnimationId()
{
	return this->_animationId;
}

int Message::getClothesId()
{
	return this->_clothesId;
}

int Message::getBgImageId()
{
	return this->_bgImageId;
}

int Message::getNextMessage()
{
	return this->_nextMessage;
}

int Message::getNextEvent()
{
	return this->_nextEvent;
}

int Message::getMessageX()
{
	return this->_messageX;
}

int Message::getMessageY()
{
	return this->_messageY;
}

int Message::getCharacterX()
{
	return this->_characterX;
}

int Message::getCharacterY()
{
	return this->_characterY;
}

std::vector<int> Message::getShowCharacters()
{
	return this->_showCharacters;
}

bool Message::getSurfaceStatus()
{
	return this->_surfaceStatus;
}

bool Message::getTextureStatus()
{
	return this->_textureStatus;
}

void Message::draw()
{
	if (this->_surfaceStatus) {
		this->_dest_rect = { this->_messageX, this->_messageY, this->_surface->w, this->_surface->h };
		if (this->_textureStatus) {
			SDL_RenderCopy(this->_renderer, this->_texture, NULL, &this->_dest_rect);
		}
		else {
			std::cout << "Message id: " << std::to_string(this->_id);
			std::cout << " texture status: false" << std::endl;
		}
	}
	else {
		std::cout << "Message id: " << std::to_string(this->_id);
		std::cout << " surface status: false" << std::endl;
	}
}

bool Message::_loadSurface()
{
	this->_surface = TTF_RenderText_Solid(this->_font, this->_text.c_str(), {255, 255, 255});
	if (this->_surface == NULL) {
		printf("Unable to make text surface! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool Message::_loadTexture()
{
	this->_texture = SDL_CreateTextureFromSurface(this->_renderer, this->_surface);
	if (this->_texture == NULL) {
		printf("Unable to make text texture! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
