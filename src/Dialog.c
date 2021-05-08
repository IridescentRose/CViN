#include "Dialog.h"
#include <stdbool.h>
#include "Sprite.h"
#include <SDL_ttf.h>
#include "WindowContext.h"
struct Sprite* sprite;
bool dialog_show;

char* cname, *ctext;

SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Surface* textSurface, *nameSurface;

TTF_Font* font;

void CVIN_Dialog_Init(){
    TTF_Init();
    dialog_show = false;
    sprite = CVIN_Sprite_Create("assets/dialog.png");
    sprite->rect.y = 480;
    font = TTF_OpenFont("assets/ARIAL.TTF", 40);;
}

void CVIN_Dialog_Cleanup(){
    dialog_show = false;
    TTF_CloseFont(font);
    TTF_Quit();
}

void CVIN_Dialog_Show(){
    dialog_show = true;
}
void CVIN_Dialog_Hide(){
    dialog_show = false;
}

SDL_Rect textLocation = { 96, 484, 0, 0 };
SDL_Rect textLocation2 = { 40, 548, 0, 0 };

void CVIN_Dialog_Text(char* name, char* text){
    cname = name;
    ctext = text;
}

void CVIN_Dialog_Draw(){
    if(dialog_show) {
        CVIN_Sprite_Render(sprite);


        nameSurface = TTF_RenderText_Blended_Wrapped(font, cname, foregroundColor, 1240);
        if(nameSurface) {
            textLocation.w = nameSurface->w;
            textLocation.h = nameSurface->h;
        }
        textSurface = TTF_RenderText_Blended_Wrapped(font, ctext, foregroundColor, 1240);

        if(textSurface) {
            textLocation2.w = textSurface->w;
            textLocation2.h = textSurface->h;
        }
        SDL_Texture *nTex = SDL_CreateTextureFromSurface(CVIN_Window_Renderer, nameSurface);
        SDL_FreeSurface(nameSurface);

        SDL_Texture *tTex = SDL_CreateTextureFromSurface(CVIN_Window_Renderer, textSurface);
        SDL_FreeSurface(textSurface);

        SDL_RenderCopy(CVIN_Window_Renderer, nTex, NULL, &textLocation);
        SDL_RenderCopy(CVIN_Window_Renderer, tTex, NULL, &textLocation2);
    }
}