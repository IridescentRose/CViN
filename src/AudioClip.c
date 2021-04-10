//
// Created by Nathan Bourgeois on 4/10/21.
//
#include <SDL.h>
#include "AudioClip.h"

struct AudioClip* CVIN_AudioClip_Create(const char* file, bool music){
    struct AudioClip* clip = calloc(1, sizeof(struct AudioClip));
    clip->isMusic = music;

    if(music){
        clip->music = Mix_LoadMUS(file);
    }else{
        clip->chunk = Mix_LoadWAV(file);
    }

    return clip;
}

void CVIN_AudioClip_Play(struct AudioClip* clip){
    if(clip->music){
        Mix_FadeOutMusic(200);
        SDL_Delay(200);
        Mix_FadeInMusic(clip->music, 0, 200);
    }else{
        Mix_PlayChannel(-1, clip->chunk, 0);
    }
}

void CVIN_AudioClip_Destroy(struct AudioClip* clip){
    if(clip->music){
        Mix_FreeMusic(clip->music);
    }else{
        Mix_FreeChunk(clip->chunk);
    }

    free(clip);
}