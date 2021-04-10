//
// Created by Nathan Bourgeois on 4/10/21.
//

#ifndef CVIN_AUDIOCLIP_H
#define CVIN_AUDIOCLIP_H

#include <stdbool.h>
#include "SDL_mixer.h"

struct AudioClip {
    Mix_Music* music;
    Mix_Chunk* chunk;
    bool isMusic;
};

struct AudioClip* CVIN_AudioClip_Create(const char* file, bool music);

void CVIN_AudioClip_Play(struct AudioClip* clip);

void CVIN_AudioClip_Destroy(struct AudioClip* clip);

#endif //CVIN_AUDIOCLIP_H
