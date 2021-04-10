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

/**
 * Creates a brand new sprite
 * @param file - Image file to load. Must be PNG, JPG, WEBP, or TIF
 * @param rect - Rectangle that defines X/Y and W/H
 * @return - Brand new sprite.
 */
struct Sprite* CVIN_Sprite_Create(const char* file, SDL_Rect rect);

/**
 * Draws a sprite onto the screen
 * @param sprite - Sprite to be drawn.
 */
void CVIN_Sprite_Render(struct Sprite* sprite);

/**
 * Destroys and frees a sprite
 * @param sprite - Sprite to be destroyed.
 */
void CVIN_Sprite_Destroy(struct Sprite* sprite);

#endif //CVIN_SPRITE_H
