#include "Control.h"

void Control::add(int x)
{
	this->_keys.push_back(x);
}

void Control::clear()
{
	this->_keys.clear();
}

bool Control::get(Action action)
{
	for (int i = 0; i < this->_keys.size(); i++) {
		if (this->_keys[i] == action) {
			return true;
		}
	}
	return false;
}
