#include <SDL.h>
#include "src/WindowContext.h"
#include "src/Sprite.h"
#include <stdbool.h>

int main(int argc, char ** argv){
    CVIN_Window_Init("CVIN", 1280, 720);

    SDL_Rect temp = { 5, 5, 320, 240 };
    struct Sprite* sprt = CVIN_Sprite_Create("test.png", temp);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        CVIN_Window_Clear();
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }

        CVIN_Sprite_Render(sprt);
        CVIN_Window_Refresh();
    }

    CVIN_Sprite_Destroy(sprt);
    CVIN_Window_Cleanup();
    return 0;
}