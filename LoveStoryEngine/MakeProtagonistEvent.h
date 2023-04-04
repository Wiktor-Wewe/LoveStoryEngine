#pragma once
#include <string>
#include <vector>

class MakeProtagonistEvent
{
public:
	MakeProtagonistEvent(std::string name, std::string text,
		std::vector<std::vector<int>> faces,
		std::vector<std::vector<int>> skins,
		std::vector<std::vector<int>> hairs,
		int nextMessageId)
	{
		this->_name = name;
		this->_text = text;
		this->_faces = faces;
		this->_skins = skins;
		this->_hairs = hairs;
		this->_nextMessageId = nextMessageId;
	}

	std::string getName();
	std::string getText();
	std::vector<std::vector<int>> getFaces();
	std::vector<std::vector<int>> getSkins();
	std::vector<std::vector<int>> getHairs();
	int getNextMessageId();

private:
	std::string _name;
	std::string _text;

	std::vector<std::vector<int>> _faces;
	std::vector<std::vector<int>> _skins;
	std::vector<std::vector<int>> _hairs;
	int _nextMessageId;
};

