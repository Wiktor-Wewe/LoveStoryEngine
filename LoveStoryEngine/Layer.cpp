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

    SDL_SetRenderTarget(this->_renderer, NULL);
}

void Layer::clear()
{
    this->_images.clear();
    this->_imagesPositions.clear();
    this->_texts.clear();
    this->_textsPositions.clear();

    SDL_SetRenderTarget(this->_renderer, this->_texture);
    SDL_RenderClear(this->_renderer);
    SDL_SetRenderTarget(this->_renderer, NULL);
}

bool Layer::addImage(Image* img, SDL_Rect& position)
{
    if (img != nullptr && img->getTextureStatus()) {
        this->_images.push_back(img);
        this->_imagesPositions.push_back(&position);
        return true;
    }
    return false;
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

bool Layer::addTextTexture(std::string text, SDL_Rect& position, TTF_Font* font, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        return false;
    }

    SDL_FreeSurface(surface);

    this->_texts.push_back(texture);
    this->_textsPositions.push_back(&position);

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
