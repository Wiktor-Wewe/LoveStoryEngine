#include "OptionWindows.h"

bool OptionWindows::make()
{
    SDL_Color color = { 255, 255, 255, 255 };

    // make textures and positions from text
    int positionY = 100;
    for (int i = 0; i < this->_texts.size(); i++) {
        SDL_Surface* surface = TTF_RenderText_Solid(this->_font, this->_texts[i].c_str(), color);
        if (surface == nullptr) {
            return false;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
        if (texture == nullptr) {
            SDL_FreeSurface(surface);
            return false;
        }

        int w = surface->w;
        int h = surface->h;
        SDL_FreeSurface(surface);

        this->_textsTextures.push_back(texture);

        if (i > 0) {
            positionY += 50 + (this->_textsPositions[i - 1]->h);
        }

        SDL_Rect* position = new SDL_Rect{ (640/2) - (w/2), positionY, w, h };
        this->_textsPositions.push_back(position);
    }
    
    // make position to frames texts
    for (int i = 0; i < this->_textsPositions.size(); i++) {
        int x = (640 / 2) - (280 / 2);
        int y = this->_textsPositions[i]->y - 5;
        SDL_Rect* rect = new SDL_Rect{ x, y, 280, 35 };
        this->_textsFramesPositions.push_back(rect);
    }

    // make texture
    SDL_SetRenderTarget(this->_renderer, this->_texture);

    for (int i = 0; i < this->_texts.size(); i++) {
        SDL_RenderCopy(this->_renderer, this->_textFrameTexture, NULL, this->_textsFramesPositions[i]);
    }

    for (int i = 0; i < this->_textsTextures.size(); i++) {
        SDL_RenderCopy(this->_renderer, this->_textsTextures[i], NULL, this->_textsPositions[i]);
    }

    this->update();

    return true;
}

void OptionWindows::update()
{
    SDL_SetRenderTarget(this->_renderer, this->_textureWithSelect);
    SDL_RenderClear(this->_renderer);
    SDL_RenderCopy(this->_renderer, this->_texture, NULL, NULL);
    SDL_RenderCopy(this->_renderer, this->_selectedFrame, NULL, this->_textsFramesPositions[this->_selected]);
    SDL_SetRenderTarget(this->_renderer, NULL);
}

SDL_Texture* OptionWindows::getTexture()
{
    return this->_texture;
}

SDL_Texture* OptionWindows::getTextureWithSelect()
{
    return this->_textureWithSelect;
}

int OptionWindows::getSelectedId()
{
    return this->_selected;
}

void OptionWindows::setSelect(int dy)
{
    if (dy > 0) {
        if (this->_selected + dy < this->_texts.size()) {
            this->_selected += dy;
        }
        else {
            this->_selected = 0;
        }
    }
    else if (dy < 0) {
        if (this->_selected + dy < 0) {
            this->_selected = this->_texts.size() - 1;
        }
        else {
            this->_selected += dy;
        }
    }
}

void OptionWindows::setTexts(std::vector<std::string> texts)
{
    this->_texts = texts;
}
