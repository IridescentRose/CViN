//
// Created by Nathan Bourgeois on 4/9/21.
//
#include "SDL_image.h"
#include "WindowContext.h"
#include "Sprite.h"

struct Sprite* CVIN_Sprite_Create(const char* file) {
    struct Sprite* sprite = calloc(1, sizeof(struct Sprite));

    sprite->image = IMG_Load(file);

    if(sprite->image == NULL){
        printf("ERROR: Image %s could not be loaded!\n", file);
        exit(-1);
    }
    sprite->isShown = false;

    sprite->texture = SDL_CreateTextureFromSurface(CVIN_Window_Renderer, sprite->image);

    if(sprite->texture == NULL){
        printf("ERROR: Texture %s could not be loaded!\n", file);
        exit(-1);
    }

    sprite->rect.x = 0;
    sprite->rect.y = 0;
    sprite->rect.w = sprite->image->w;
    sprite->rect.h = sprite->image->h;
    return sprite;
}

void CVIN_Sprite_Render(struct Sprite* sprite){
    SDL_RenderCopy(CVIN_Window_Renderer, sprite->texture, NULL, &sprite->rect);
}

void CVIN_Sprite_Destroy(struct Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    SDL_FreeSurface(sprite->image);

    free(sprite);
}