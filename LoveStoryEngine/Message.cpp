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
