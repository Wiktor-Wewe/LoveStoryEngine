#pragma once
#include <vector>
#include "Character.h"
#include "ChooseClothesEvent.h"
#include "Event.h"
#include "Image.h"
#include "MakeProtagonistEvent.h"
#include "Message.h"
#include "Music.h"
#include "Protagonist.h"
#include "Sfx.h"
#include <fstream>
#include <iostream>

class Story
{
public:
	Story(std::fstream* file = nullptr)
	{
		this->_name = std::string();
		this->_info = std::string();
		this->_author = std::string();
		this->_date = std::string();

		this->_Characters = std::vector<Character>();
		this->_CCEvents = std::vector<ChooseClothesEvent>();
		this->_Events = std::vector<Event>();
		this->_Images = std::vector<Image>();
		this->_MPEvent = (MakeProtagonistEvent*)malloc(sizeof(MakeProtagonistEvent));
		this->_Messages = std::vector<Message>();
		this->_Musics = std::vector<Music>();
		this->_Player = (Protagonist*)malloc(sizeof(Protagonist));
		this->_Sfxs = std::vector<Sfx>();

		if (file != nullptr) {
			this->loadStory(file);
		}
	}

	std::string getName();
	std::string getInfo();
	std::string getAuthor();
	std::string getDate();

	int loadStory(std::fstream* file);
	int play();

private:
	std::vector<Character> _Characters;
	std::vector<ChooseClothesEvent> _CCEvents;
	std::vector<Event> _Events;
	std::vector<Image> _Images;
	MakeProtagonistEvent* _MPEvent;
	std::vector<Message> _Messages;
	std::vector<Music> _Musics;
	Protagonist* _Player;
	std::vector<Sfx> _Sfxs;

	std::string _name;
	std::string _info;
	std::string _author;
	std::string _date;
	std::string _compilationInfo;

	// play
	Event* _findEventById(int id);
	Message* _findMessageById(int id);
	MakeProtagonistEvent* _getMpei();
	ChooseClothesEvent* _findCceById(int id);
	Image* _findImageById(int id);
	Music* _findMusicById(int id);
	Sfx* _findSfxById(int id);
	Protagonist* _getPlayer();

	// show
	void _clsAndShowInfo();
	void _showMessage(Message* m);
	void _showEvent(Event* e);
	void _showMPE(MakeProtagonistEvent* mpe);
	void _showCCE(ChooseClothesEvent* cce);
	void _printInfoAboutPlayer();

	void _setName(std::string name);
	void _setInfo(std::string info);
	void _setAuthor(std::string author);
	void _setDate(std::string date);

	// load
	bool _isHeaderOkay(std::fstream* file);
	bool _isSizeOkay(std::fstream* file);
	void _loadGlobalInfo(std::fstream* file);
	void _loadCharacters(std::fstream* file);
	void _loadCCE(std::fstream* file);
	void _loadEvents(std::fstream* file);
	void _loadImages(std::fstream* file);
	void _loadMPE(std::fstream* file);
	void _loadMessages(std::fstream* file);
	void _loadMusics(std::fstream* file);
	void _loadSfxs(std::fstream* file);
	void _loadCompilationInfo(std::fstream* file);
	bool _checkEndOfFile(std::fstream* file);


	void _swapBytes(int& x);
	void _wipeStrBuff(char* buff);
	void _wipeStrBuff(char* buff, int size);
};

