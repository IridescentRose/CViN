#ifndef CVIN_PROGRAM_H
#define CVIN_PROGRAM_H

#include "Tokenizer.h"
#include <stdbool.h>

typedef enum {
    PROGRAM_CHARACTER = 0,
    PROGRAM_SPRITE = 1,
    PROGRAM_MUSIC = 2,
    PROGRAM_SOUND = 3
} VariableType;

struct Variable {
    VariableType type;
    char* name;
    void* data;
};

typedef enum {
    STATEMENT_TYPE_EXIT = 0,
    STATEMENT_TYPE_SHOW = 1,
    STATEMENT_TYPE_PLAY = 2,
    STATEMENT_TYPE_SAY = 3,
    STATEMENT_TYPE_STOP = 4,
    STATEMENT_TYPE_HIDE = 5
} StatementType;

struct Statement{
    StatementType type;
    void* paramData;
};

struct ShowInfo{
    char* name;
    bool bg;
    float x, y;
    bool isShown;
};

struct SaysInfo{
    char* name;
    char* text;
};

struct StatementBlock{
    struct Statement* body;
    unsigned int len;
};

struct Program{
    struct Variable vars[1024];
    unsigned int varCount;
    struct StatementBlock block;
};

/**
 * Parses a program from the token array using an iterator
 * @param token - Token Array Iterator
 * @return - A "compiled" program to be executed on the VM
 */
struct Program parseProgram(struct TokenArrayIterator token);

#endif //CVIN_PROGRAM_H
