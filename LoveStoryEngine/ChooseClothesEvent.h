#pragma once
#include <string>
#include <vector>
class ChooseClothesEvent
{
public:
	ChooseClothesEvent(int id, std::string text, std::vector<std::vector<int>> clothes, int nextMessageId)
	{
		this->_id = id;
		this->_text = text;
		this->_clothes = clothes;
		this->_nextMessageId = nextMessageId;
	}
	int getId();
	std::string getText();
	std::vector<std::vector<int>> getClothes();
	int getNextMessageId();

private:
	int _id;
	std::string _text;
	std::vector<std::vector<int>> _clothes;
	int _nextMessageId;
};

