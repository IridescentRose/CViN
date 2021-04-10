//
// Created by Nathan Bourgeois on 4/7/21.
//

#ifndef CVIN_WINDOWCONTEXT_H
#define CVIN_WINDOWCONTEXT_H

//Define the window management system

struct Color{
    uint8_t r, g, b, a;
};

/**
 * Creates a brand new Window Context.
 * @param title - The title for the window
 * @param width - The width of the window
 * @param height - The height of the window
 */
void CVIN_Window_Init(const char* title, int width, int height);

/**
 * Changes the background color of the window.
 * @param color - The new color of the window background
 */
void CVIN_Window_Background_Color(struct Color color);

/**
 * Clears the Window.
 */
void CVIN_Window_Clear();

/**
 * Displays the contents rendered to the window.
 */
void CVIN_Window_Refresh();

/**
 * Cleans up the Window Context.
 */
void CVIN_Window_Cleanup();

/**
 * General purpose SDL_Renderer.
 */
extern SDL_Renderer* CVIN_Window_Renderer;

#endif
