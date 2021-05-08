#include "Program.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sprite.h"
#include "AudioClip.h"

VariableType parseType(struct TokenArrayIterator* token){
    if(strcmp(TKAI_front(*token).ptr, "SPRITE") == 0){
        return PROGRAM_SPRITE;
    }
    if(strcmp(TKAI_front(*token).ptr, "CHARACTER") == 0){
        return PROGRAM_CHARACTER;
    }
    if(strcmp(TKAI_front(*token).ptr, "MUSIC") == 0){
        return PROGRAM_MUSIC;
    }
    if(strcmp(TKAI_front(*token).ptr, "SOUND") == 0){
        return PROGRAM_SOUND;
    }

    fprintf(stderr, "Expected valid variable type, found \"%s\"!\n", TKAI_front(*token).ptr);
    exit(-1);
}

void* parseSprite(struct TokenArrayIterator* token) {
    TKAI_next(token);
    if(strcmp(TKAI_front(*token).ptr, "FILE") == 0) {
        TKAI_next(token);

        if(TKAI_front(*token).ptr[0] == '"' && TKAI_front(*token).ptr[TKAI_front(*token).len - 1] == '"'){
            TKAI_front(*token).ptr[TKAI_front(*token).len - 1] = 0;

            return (void*)CVIN_Sprite_Create(&TKAI_front(*token).ptr[1]);
        }else {
            fprintf(stderr, "Expected filename beginning and ending with `\"`, found \"%s\"!\n", TKAI_front(*token).ptr);
            exit(-1);
        }

    } else {
        fprintf(stderr, "Expected FILE, found \"%s\"!\n", TKAI_front(*token).ptr);
        exit(-1);
    }
}

void* parseCharacter(struct TokenArrayIterator* token) {
    TKAI_next(token);
    if(strcmp(TKAI_front(*token).ptr, "SPRITE") == 0) {
        TKAI_next(token);

        //It's a string - this will need to be resolved dynamically.
        return (void*)TKAI_front(*token).ptr;
    } else {
        fprintf(stderr, "Expected FILE, found \"%s\"!\n", TKAI_front(*token).ptr);
        exit(-1);
    }
}

void* parseSound(struct TokenArrayIterator* token) {
    TKAI_next(token);
    if(strcmp(TKAI_front(*token).ptr, "FILE") == 0) {
        TKAI_next(token);

        if(TKAI_front(*token).ptr[0] == '"' && TKAI_front(*token).ptr[TKAI_front(*token).len - 1] == '"'){
            TKAI_front(*token).ptr[TKAI_front(*token).len - 1] = 0;

            return (void*)CVIN_AudioClip_Create(&TKAI_front(*token).ptr[1], false);
        }else {
            fprintf(stderr, "Expected filename beginning and ending with `\"`, found \"%s\"!\n", TKAI_front(*token).ptr);
            exit(-1);
        }

    } else {
        fprintf(stderr, "Expected FILE, found \"%s\"!\n", TKAI_front(*token).ptr);
        exit(-1);
    }
}

void* parseMusic(struct TokenArrayIterator* token) {
    TKAI_next(token);
    if(strcmp(TKAI_front(*token).ptr, "FILE") == 0) {
        TKAI_next(token);

        if(TKAI_front(*token).ptr[0] == '"' && TKAI_front(*token).ptr[TKAI_front(*token).len - 1] == '"'){
            TKAI_front(*token).ptr[TKAI_front(*token).len - 1] = 0;

            return (void*)CVIN_AudioClip_Create(&TKAI_front(*token).ptr[1], true);
        }else {
            fprintf(stderr, "Expected filename beginning and ending with `\"`, found \"%s\"!\n", TKAI_front(*token).ptr);
            exit(-1);
        }

    } else {
        fprintf(stderr, "Expected FILE, found \"%s\"!\n", TKAI_front(*token).ptr);
        exit(-1);
    }
}

//Parse post "DEFINE"
struct Variable parseVariable(struct TokenArrayIterator* token) {
    //Toss the define
    TKAI_next(token);

    struct Variable var;
    var.name = TKAI_front(*token).ptr;

    //We expect "as" to be the specifier of type.
    TKAI_next(token);

    if(strcmp(TKAI_front(*token).ptr, "as") == 0){
        //Valid, find type
        TKAI_next(token);

        var.type = parseType(token);
        TKAI_next(token);

        //If we have a with, then we can determine what to do per type.
        if(strcmp(TKAI_front(*token).ptr, "with") == 0) {
            switch (var.type) {
                case PROGRAM_SPRITE: {
                    var.data = parseSprite(token);
                    TKAI_next(token);
                    break;
                }

                case PROGRAM_MUSIC: {
                    var.data = parseMusic(token);
                    TKAI_next(token);
                    break;
                }

                case PROGRAM_CHARACTER: {
                    var.data = parseCharacter(token);
                    TKAI_next(token);
                    break;
                }

                case PROGRAM_SOUND: {
                    var.data = parseSound(token);
                    TKAI_next(token);
                    break;
                }

                default: {
                    fprintf(stderr, "Unexpected variable type!\n");
                    exit(-1);
                }
            }
        }else {
            fprintf(stderr, "Error: Expected \"with\" in define declaration, found \"%s\"!\n", TKAI_front(*token).ptr);
            exit(-1);
        }

    } else {
        fprintf(stderr, "Error: Expected \"as\" in define declaration, found \"%s\"!\n", TKAI_front(*token).ptr);
        exit(-1);
    }
    return var;
}

struct Program parseProgram(struct TokenArrayIterator token){
    struct Program result;
    result.varCount = 0;

    struct Statement statements[4096];
    unsigned int sLen = 0;

    //While the position is not at the end.
    while(token.pos != token.tokens.len){
        //Let's parse!

        //First type of statement is the "DEFINE"
        //Other type of statements are "calls"

        if(strcmp(TKAI_front(token).ptr, "define") == 0) {
            //We have a variable declaration
            result.vars[result.varCount] = parseVariable(&token);
            result.varCount++;
        } else {
            //We have some sort of statement...
            if(strcmp(TKAI_front(token).ptr, "exit") == 0){
                //EXIT
                statements[sLen].type = STATEMENT_TYPE_EXIT;
                //No argument data
                TKAI_next(&token);

            } else if(strcmp(TKAI_front(token).ptr, "play") == 0){
                //PLAY
                statements[sLen].type = STATEMENT_TYPE_PLAY;
                //Next token is sound name.
                TKAI_next(&token);
                statements[sLen].paramData = (void*)TKAI_front(token).ptr;
                TKAI_next(&token);

            }else if(strcmp(TKAI_front(token).ptr, "stop") == 0){
                //PLAY
                statements[sLen].type = STATEMENT_TYPE_STOP;
                //Next token is sound name.
                TKAI_next(&token);
                statements[sLen].paramData = (void*)TKAI_front(token).ptr;
                TKAI_next(&token);

            }else if(strcmp(TKAI_front(token).ptr, "hide") == 0){
                //PLAY
                statements[sLen].type = STATEMENT_TYPE_HIDE;
                //Next token is sprite name.
                TKAI_next(&token);
                statements[sLen].paramData = (void*)TKAI_front(token).ptr;
                TKAI_next(&token);

            } else if(strcmp(TKAI_front(token).ptr, "show") == 0){
                //SHOW
                statements[sLen].type = STATEMENT_TYPE_SHOW;
                //Next token is sprite name.
                TKAI_next(&token);

                struct ShowInfo* showInfo = malloc(sizeof(struct ShowInfo));
                showInfo->name = (void*)TKAI_front(token).ptr;
                TKAI_next(&token);
                showInfo->isShown = false;

                if(strcmp(TKAI_front(token).ptr, "at") == 0){
                    //At X Y
                    TKAI_next(&token);

                    showInfo->x = strtof(TKAI_front(token).ptr, NULL);
                    TKAI_next(&token);
                    showInfo->y = strtof(TKAI_front(token).ptr, NULL);
                    TKAI_next(&token);
                } else if (strcmp(TKAI_front(token).ptr, "as") == 0) {
                    //As BG
                    TKAI_next(&token);
                    if(strcmp(TKAI_front(token).ptr, "BG") == 0){
                        showInfo->bg = true;
                        TKAI_next(&token);
                    }else {
                        fprintf(stderr, "Error: Expected BG as parameter for `as` block. Found \"%s\"!\n", TKAI_front(token).ptr);
                        exit(-1);
                    }
                }

                statements[sLen].paramData = (void*)showInfo;
            } else {
                //SAYS
                statements[sLen].type = STATEMENT_TYPE_SAY;

                struct SaysInfo* saysInfo = malloc(sizeof(struct SaysInfo));
                statements[sLen].paramData = saysInfo;
                saysInfo->name = TKAI_front(token).ptr;

                TKAI_next(&token);

                if(strcmp(TKAI_front(token).ptr, "says") == 0) {

                    char accumulator[512] = {0};
                    unsigned int accPos = 0;

                    TKAI_next(&token);
                    strcat(&accumulator[accPos], &TKAI_front(token).ptr[1]);
                    accPos += TKAI_front(token).len - 1;
                    TKAI_next(&token);
                    strcat(&accumulator[accPos], " ");
                    accPos += 1;

                    while (accPos < 512 && TKAI_front(token).ptr[TKAI_front(token).len - 1] != '"') {
                        if (accPos + TKAI_front(token).len < 512) {
                            strcat(&accumulator[accPos], TKAI_front(token).ptr);
                            accPos += TKAI_front(token).len;
                            strcat(&accumulator[accPos], " ");
                            accPos += 1;

                            TKAI_next(&token);
                        } else {
                            fprintf(stderr, "Error: String is longer than 512 characters!");
                            exit(-1);
                        }
                    }

                    //This case we still need to add the last part of the string
                    TKAI_front(token).ptr[TKAI_front(token).len - 1] = 0;
                    strcat(&accumulator[accPos], TKAI_front(token).ptr);
                    TKAI_next(&token);

                    //Create independent instance
                    saysInfo->text = strdup(accumulator);

                } else {
                    fprintf(stderr, "Error: Expected says keyword. Found \"%s\"!\n", TKAI_front(token).ptr);
                    exit(-1);
                }
            }
            sLen += 1;
        }
    }

    //Copy statements to program
    result.block.len = sLen;
    result.block.body = (struct Statement*) malloc(sizeof(struct Statement) * sLen);

    for(int i = 0; i < result.block.len; i++){
        result.block.body[i] = statements[i];
    }
    return result;
}