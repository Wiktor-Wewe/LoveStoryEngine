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
		esc = 5,
		special1 = 6,
		special2 = 7
	};

	void add(int x);
	void clear();
	bool get(Action action);
	bool getStatus();

private:
	std::vector<int> _keys;
	bool _status;
};

