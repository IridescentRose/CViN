#include "Tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TokenArray tokenize(const char* filepath){
    FILE* fp = fopen(filepath, "r");

    struct TokenArray result;
    result.len = 0;
    result.slices = NULL;

    char* reserve[4096];
    unsigned short rLen = 0;

    if(fp != NULL){

        //Get tokens into a reserved area
        char line[255];
        char *token;

        while(fgets(line, sizeof line, fp) != NULL){
            //Ignore comments and blank lines
            if((line[0] != '/' && line[1] != '/') && line[0] != '\n') {

                token = strtok(line, " \n");;
                while (token != NULL) {
                    //Add entry

                    //Duplicate - strtok makes an aliased reference into line from what I can tell
                    //We need a separate pointer for this to work
                    reserve[rLen] = strdup(token);
                    rLen++;

                    token = strtok(NULL, " \n");
                }
            }
        }

        result.len = rLen;
        result.slices = malloc(sizeof(struct StringSlice) * rLen);
        memset(result.slices, 0, result.len * sizeof(struct StringSlice));

        for(int i = 0; i < result.len; i++) {
            result.slices[i].ptr = reserve[i];
            result.slices[i].len = strlen(reserve[i]);
        }
    }

    fclose(fp);
    return result;
}


struct StringSlice TKAI_front(struct TokenArrayIterator tkArray){
    return tkArray.tokens.slices[tkArray.pos];
}

void TKAI_next(struct TokenArrayIterator* tkArray){
    if(tkArray->pos < tkArray->tokens.len) {
        tkArray->pos += 1;
    }
}