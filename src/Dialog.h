#ifndef CVIN_DIALOG_H
#define CVIN_DIALOG_H

/**
 * Initialize Dialog and Fonts
 */
void CVIN_Dialog_Init();

/**
 * Draw Dialog
 */
void CVIN_Dialog_Draw();

/**
 * Show the Dialog Box
 */
void CVIN_Dialog_Show();

/**
 * Hide the Dialog Box
 */
void CVIN_Dialog_Hide();

/**
 * Change the dialog text
 * @param name - Character Name
 * @param text - Dialog Text
 */
void CVIN_Dialog_Text(char* name, char* text);

/**
 * Clean up the box and fonts used.
 */
void CVIN_Dialog_Cleanup();

#endif //CVIN_DIALOG_H
