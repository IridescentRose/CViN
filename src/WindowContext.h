//
// Created by Nathan Bourgeois on 4/7/21.
//

#ifndef CVIN_WINDOWCONTEXT_H
#define CVIN_WINDOWCONTEXT_H

//Define the window management system

void CVIN_Window_Init(const char* title, int width, int height);

void CVIN_Window_Background_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void CVIN_Window_Clear();

void CVIN_Window_Refresh();
void CVIN_Window_Cleanup();

extern SDL_Renderer* CVIN_Window_Renderer;

#endif
