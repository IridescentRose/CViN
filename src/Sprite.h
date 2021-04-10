//
// Created by Nathan Bourgeois on 4/9/21.
//

#ifndef CVIN_SPRITE_H
#define CVIN_SPRITE_H

#include "SDL.h"

struct Sprite{
    SDL_Surface* image;
    SDL_Texture* texture;
    SDL_Rect rect;
};

struct Sprite* CVIN_Sprite_Create(const char* file, SDL_Rect rect);

void CVIN_Sprite_Render(struct Sprite* sprite);

void CVIN_Sprite_Destroy(struct Sprite* sprite);

#endif //CVIN_SPRITE_H
