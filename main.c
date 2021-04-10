#include <SDL.h>
#include "src/WindowContext.h"
#include <stdbool.h>

int main(int argc, char ** argv){
    CVIN_Window_Init("CVIN", 1280, 720);
    CVIN_Window_Background_Color(255, 0, 0, 255);


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

        CVIN_Window_Refresh();
    }

    CVIN_Window_Cleanup();
    return 0;
}