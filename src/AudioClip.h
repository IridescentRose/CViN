//
// Created by Nathan Bourgeois on 4/10/21.
//

#ifndef CVIN_AUDIOCLIP_H
#define CVIN_AUDIOCLIP_H

#include <stdbool.h>
#include "SDL_mixer.h"

/**
 * A basic audio sample.
 */
struct AudioClip {
    Mix_Music* music;
    Mix_Chunk* chunk;
    bool isMusic;
};

/**
 * Loads a new clip. Sound effects must be WAV, music can be OGG, FLAC, MOD, or MP3.
 * @param file - File to be loaded
 * @param music - Whether or not this is a "music" file
 * @return - Returns an audio clip
 */
struct AudioClip* CVIN_AudioClip_Create(const char* file, bool music);

/**
 * Plays an audio clip. If it is music, there is a fade transition.
 * @param clip - Clip to be played
 */
void CVIN_AudioClip_Play(struct AudioClip* clip);

/**
 * Destroys and frees a clip.
 * @param clip - The clip to be destroyed
 */
void CVIN_AudioClip_Destroy(struct AudioClip* clip);

#endif //CVIN_AUDIOCLIP_H
