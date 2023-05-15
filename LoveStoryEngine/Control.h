#pragma once
#include <vector>
class Control
{
public:
	enum Action {
		go = 0,
		left = 1,
		right = 2,
		up = 3,
		down = 4,
		esc = 5
	};

	void add(int x);
	void clear();
	bool get(Action action);
	
private:
	std::vector<int> _keys;
};

