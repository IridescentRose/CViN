#include <SDL.h>
#include "src/WindowContext.h"
#include <stdbool.h>
#include "src/Tokenizer.h"
#include "src/Program.h"
#include "src/VM.h"
#include "src/Dialog.h"

int main(){
    struct TokenArray array = tokenize("game/game.cvin");

    struct TokenArrayIterator iter;
    iter.tokens = array;
    iter.pos = 0;

    CVIN_Window_Init("CVIN", 1280, 720);
    CVIN_Dialog_Init();
    CVIN_Dialog_Show();

    struct Program prog = parseProgram(iter);
    struct VM vm;
    vm.program = &prog;
    vm.instructionPointer = 0;
    vm.hasExec = false;


    bool quit = false;
    SDL_Event event;
    while (!quit) {
        CVIN_Window_Clear();
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN: {
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(vm.hasExec) {
                        stepVM(&vm);
                    }
                }
            }

        }

        executeVM(&vm);
        drawVM(&vm);
        CVIN_Dialog_Draw();
        CVIN_Window_Refresh();
    }

    CVIN_Dialog_Cleanup();
    CVIN_Window_Cleanup();
    return 0;
}