#include "Control.h"

void Control::add(int x)
{
	this->_status = true;
	this->_keys.push_back(x);
}

void Control::clear()
{
	this->_status = false;
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

bool Control::getStatus()
{
	return this->_status;
}
