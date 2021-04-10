//
// Created by Nathan Bourgeois on 4/7/21.
//

#include "SDL.h"
#include "WindowContext.h"

SDL_Window * window;
SDL_Renderer * renderer;

void CVIN_Window_Init(const char* title, int width, int height){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void CVIN_Window_Background_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void CVIN_Window_Clear(){
    SDL_RenderClear(renderer);
}

void CVIN_Window_Refresh(){
    SDL_RenderPresent(renderer);
}

void CVIN_Window_Cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}