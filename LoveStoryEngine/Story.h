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
#include "Scene.h"
#include <fstream>
#include <iostream>

class Story
{
public:
	Story(SDL_Renderer* renderer, std::fstream* file = nullptr)
	{
		this->_renderer = renderer;
		this->_font = TTF_OpenFont("arial.ttf", 20);

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
		this->_scene = new Scene(this->_renderer);
		this->_currentMusicId = 0;

		if (this->loadBase() && file != nullptr) {
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

	// base find and get
	Event* _findEventById(int id);
	Message* _findMessageById(int id);
	MakeProtagonistEvent* _getMpei();
	ChooseClothesEvent* _findCceById(int id);
	Image* _findImageById(int id);
	Music* _findMusicById(int id);
	Sfx* _findSfxById(int id);
	Character* _findCharacterById(int id);
	Protagonist* _getPlayer();

	// show
	void _clsAndShowInfo();

	// message
	void _handleMessage(Message* m);
	void _showMessageInfo(Message* m);
	void _setCharacterPosition(Message* m);
	void _playMusic(Message* m);
	void _drawCharacters(Message* m);
	void _tryDrawImage(int id, int x, int y);
	Character* _tryGetCharacter(int id);

	// event
	void _handleEvent(Event* e);
	void _showEventInfo(Event* e);
	int _getSelectedOptionId(int* mouse_x, int* mouse_y, std::vector<Event::rawimage>& options);

	// mpe
	void _handleMPE(MakeProtagonistEvent* mpe);
	void _showMPEInfo(MakeProtagonistEvent* mpe);


	void _showCCE(ChooseClothesEvent* cce);
	void _printInfoAboutPlayer();
	std::string _tryGetName(Image* x, int id);
	std::string _tryGetName(Music* x, int id);
	std::string _tryGetName(Sfx* x, int id);
	std::string _tryGetName(Character* x, int id);
	
	void _setName(std::string name);
	void _setInfo(std::string info);
	void _setAuthor(std::string author);
	void _setDate(std::string date);

	// load
	bool loadBase(); //load base-default elements as images etc

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

	// play variable
	void searchNext(Message*& m, Event*& e, MakeProtagonistEvent*& mpe, ChooseClothesEvent*& cce);
	Scene* _scene;
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	int _currentMusicId;
};

