#include "SceneTest.h"

void SceneTest::addLayer()
{
    this->_layers.push_back(new Layer(this->_renderer));
}

bool SceneTest::removeLayer(int number)
{
    if (number >= 0 && number < this->_layers.size()) {
        this->_layers[number]->clear();

        auto layer = std::find(this->_layers.begin(), this->_layers.end(), this->_layers[number]);
        if (layer != this->_layers.end()) {
            this->_layers.erase(layer);
            return true;
        }
    }
    return false;
}

void SceneTest::draw()
{
    for (int i = 0; i < this->_layers.size(); i++) {
        this->_layers[i]->draw();
    }
}

void SceneTest::clear()
{
    for (int i = 0; i < this->_layers.size(); i++) {
        this->_layers[i]->clear();
    }
    this->_layers.clear();
}

Layer* SceneTest::getLayer(int number)
{
    if (number >= 0 && number < this->_layers.size()) {
        return this->_layers[number];
    }
    return nullptr;
}

Layer* SceneTest::getLastLayer()
{
    if (this->_layers.size() < 1) {
        return nullptr;
    }
    return this->_layers[this->_layers.size() - 1];
}
