//
// Created by Nathan Bourgeois on 4/7/21.
//

#include "SDL_image.h"
#include "WindowContext.h"

SDL_Window* window = NULL;
SDL_Renderer* CVIN_Window_Renderer = NULL;

void CVIN_Window_Init(const char* title, int width, int height){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    CVIN_Window_Renderer = SDL_CreateRenderer(window, -1, 0);
}

void CVIN_Window_Background_Color(struct Color c){
    SDL_SetRenderDrawColor(CVIN_Window_Renderer, c.r, c.g, c.b, c.a);
}

void CVIN_Window_Clear(){
    SDL_RenderClear(CVIN_Window_Renderer);
}

void CVIN_Window_Refresh(){
    SDL_RenderPresent(CVIN_Window_Renderer);
}

void CVIN_Window_Cleanup(){
    SDL_DestroyRenderer(CVIN_Window_Renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}