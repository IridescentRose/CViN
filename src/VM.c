#include "VM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AudioClip.h"
#include "Sprite.h"
#include "Dialog.h"

int findVariableByName(struct Program* program, char* str){
    int idx = -1;

    for(int i = 0; i < program->varCount; i++){
        if(strcmp(program->vars[i].name, str) == 0){
            return i;
        }
    }
    return idx;
}

void executeVM(struct VM* vm){
    if(!vm->hasExec && vm->instructionPointer < vm->program->block.len){
        //Execute

        struct Statement* instruction = &vm->program->block.body[vm->instructionPointer];

        switch(instruction->type){

            case STATEMENT_TYPE_EXIT: {
                exit(0);
            }

            case STATEMENT_TYPE_SHOW: {
                struct ShowInfo* showInfo = (struct ShowInfo*)instruction->paramData;
                int idx = findVariableByName(vm->program, showInfo->name);

                struct Sprite* sprite;
                if(vm->program->vars[idx].type == PROGRAM_CHARACTER){
                    idx = findVariableByName(vm->program, (char*)vm->program->vars[idx].data);
                    sprite = (struct Sprite*)vm->program->vars[idx].data;
                }else {
                    sprite = (struct Sprite*)vm->program->vars[idx].data;
                }
                sprite->isShown = true;

                if(showInfo->bg){
                    sprite->rect.x = 0;
                    sprite->rect.y = 0;
                    sprite->rect.w = 1280;
                    sprite->rect.h = 720;
                } else {
                    sprite->rect.x = (int)(showInfo->x * 1280) - sprite->rect.w / 2;
                    sprite->rect.y = (int)(showInfo->y * 720) - sprite->rect.h / 2;
                }
                stepVM(vm);
                break;
            }

            case STATEMENT_TYPE_HIDE: {
                char* id = (char*)instruction->paramData;
                int idx = findVariableByName(vm->program, id);

                if(vm->program->vars[idx].type == PROGRAM_CHARACTER) {
                    idx = findVariableByName(vm->program, (char*)vm->program->vars[idx].data);
                    ((struct Sprite*)vm->program->vars[idx].data)->isShown = false;
                } else {
                    ((struct Sprite*)vm->program->vars[idx].data)->isShown = false;
                }

                stepVM(vm);
                break;
            }

            case STATEMENT_TYPE_PLAY: {
                char* id = (char*)instruction->paramData;
                int idx = findVariableByName(vm->program, id);

                struct AudioClip* clip = (struct AudioClip*)vm->program->vars[idx].data;
                CVIN_AudioClip_Play(clip);
                if(!clip->music){
                    SDL_Delay(500);
                }
                stepVM(vm);
                break;
            }

            case STATEMENT_TYPE_STOP: {
                char* id = (char*)instruction->paramData;
                int idx = findVariableByName(vm->program, id);

                CVIN_AudioClip_Stop((struct AudioClip*)vm->program->vars[idx].data);
                stepVM(vm);
                break;
            }

            case STATEMENT_TYPE_SAY: {
                struct SaysInfo* saysInfo = (struct SaysInfo*)instruction->paramData;
                CVIN_Dialog_Text(saysInfo->name, saysInfo->text);
                vm->hasExec = true;

                break;
            }

            default: {
                fprintf(stderr, "Error: Unknown instruction type!\n");
                exit(-1);
            }
        }
    }
}

void stepVM(struct VM* vm){
    vm->instructionPointer++;
    vm->hasExec = false;
}


void drawVM(struct VM* vm){
    for(int i = 0; i < vm->program->varCount; i++){
        struct Variable* var = &vm->program->vars[i];

        if(var->type == PROGRAM_SPRITE){
            //Check the info
            struct Sprite* sprite = var->data;

            if(sprite->isShown){
                CVIN_Sprite_Render(sprite);
            }
        }
    }
}