#pragma once
#include <vector>
#include "Layer.h"
class SceneTest
{
public:
	SceneTest(SDL_Renderer* renderer) {
		this->_renderer = renderer;
	}

	void addLayer();
	bool removeLayer(int number);

	void draw();
	void clear();

	Layer* getLayer(int number);

private:
	SDL_Renderer* _renderer;
	std::vector<Layer*> _layers;

};

