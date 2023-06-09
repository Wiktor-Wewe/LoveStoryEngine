#include "Layer.h"

void Layer::draw()
{
    SDL_RenderCopy(this->_renderer, this->_texture, NULL, &this->_position);
}

void Layer::make()
{
    SDL_SetRenderTarget(this->_renderer, this->_texture);
    
    for (int i = 0; i < this->_images.size(); i++) {
        SDL_RenderCopy(this->_renderer, this->_images[i]->getTexture(), NULL, this->_imagesPositions[i]);
    }

    for (int i = 0; i < this->_texts.size(); i++) {
        SDL_RenderCopy(this->_renderer, this->_texts[i], NULL, this->_textsPositions[i]);
    }

    for (int i = 0; i < this->_textures.size(); i++) {
        SDL_RenderCopy(this->_renderer, this->_textures[i], this->_texturesPositionsSrc[i], this->_texturesPositions[i]);
    }

    SDL_SetRenderTarget(this->_renderer, NULL);
}

void Layer::clear()
{
    this->_images.clear();
    this->_imagesPositions.clear();
    this->_texts.clear();
    this->_textsPositions.clear();
    this->_textures.clear();
    this->_texturesPositions.clear();
    this->_texturesPositionsSrc.clear();
}

bool Layer::addImage(Image* img, int x, int y)
{
    if (img == nullptr || !img->getTextureStatus()) {
        return false;
    }

    int w = img->getSurface()->w;
    int h = img->getSurface()->h;
    SDL_Rect* position = new SDL_Rect {x, y, w, h};

    this->_images.push_back(img);
    this->_imagesPositions.push_back(position);
    return true;
}

bool Layer::tryRemoveImg(Image* img)
{
    auto image = std::find(this->_images.begin(), this->_images.end(), img);
    if (image != this->_images.end()) {
        int index = std::distance(this->_images.begin(), image);
        this->_images.erase(image);
        auto position = std::find(this->_imagesPositions.begin(), this->_imagesPositions.end(), this->_imagesPositions[index]);
        this->_imagesPositions.erase(position);
        return true;
    }
    return false;
}

bool Layer::addText(std::string text, int x, int y, TTF_Font* font, int r, int g, int b, int a)
{
    SDL_Color color = { r, g, b, a };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
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

    this->_texts.push_back(texture);

    SDL_Rect* position = new SDL_Rect { x, y, w, h };
    this->_textsPositions.push_back(position);

    return true;
}

bool Layer::tryRemoveText(int numberOfText)
{
    if (numberOfText < this->_texts.size()) {
        SDL_DestroyTexture(this->_texts[numberOfText]);
        auto text = std::find(this->_texts.begin(), this->_texts.end(), this->_texts[numberOfText]);
        if (text != this->_texts.end()) {
            this->_texts.erase(text);
            auto position = std::find(this->_textsPositions.begin(), this->_textsPositions.end(), this->_textsPositions[numberOfText]);
            this->_textsPositions.erase(position);
            return true;
        }
    }
    return false;
}

bool Layer::addTexture(SDL_Texture* texture, int x, int y, int w, int h, SDL_Rect* src)
{
    if (texture == NULL) {
        return false;
    }

    this->_textures.push_back(texture);
    SDL_Rect* rect = new SDL_Rect{ x, y, w, h };
    this->_texturesPositions.push_back(rect);
    this->_texturesPositionsSrc.push_back(src);
}

bool Layer::tryRemoveTexture(int numberOfTexture)
{
    if (numberOfTexture < this->_textures.size()) {
        SDL_DestroyTexture(this->_textures[numberOfTexture]);
        auto texture = std::find(this->_textures.begin(), this->_textures.end(), this->_textures[numberOfTexture]);
        if (texture != this->_textures.end()) {
            this->_textures.erase(texture);
            auto position = std::find(this->_texturesPositions.begin(), this->_texturesPositions.end(), this->_texturesPositions[numberOfTexture]);
            this->_texturesPositions.erase(position);
            auto positionSrc = std::find(this->_texturesPositionsSrc.begin(), this->_texturesPositionsSrc.end(), this->_texturesPositionsSrc[numberOfTexture]);
            this->_texturesPositionsSrc.erase(positionSrc);
            return true;
        }
    }
    return false;
}
