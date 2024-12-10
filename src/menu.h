#ifndef MENU_H
#define MENU_H

#include "sdl2.h"
#include <SDL2/SDL_mixer.h> 
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum menu_state {
    MENU_NO_FOCUS,
    MENU_PLAY_FOCUS,       // Play choice has focus
    MENU_QUIT_FOCUS,       // Quit choice has focus
    MENU_PLAY,             // Play has been chosen
    MENU_QUIT,              // Play has been chosen
    MENU_EASY_FOCUS,       // Easy difficulty has focus
    MENU_MEDIUM_FOCUS,     // Medium difficulty has focus
    MENU_HARD_FOCUS,        // Hard difficulty has focus
    MENU_STATE
};

struct menu {
    enum menu_state state;          // The choice of the user
    struct spritesheet *background; // The menu background
    struct spritesheet *title;      // The title sprite
    struct spritesheet *play;       // The play sprite
    struct spritesheet *quit;       // The quit sprite
    struct spritesheet *difficulty; // New
    struct spritesheet *easy;       // New
    struct spritesheet *medium;     // New
    struct spritesheet *hard;
    int selected_difficulty;
    SDL_Renderer *renderer;         // The renderer
    Mix_Chunk *click_sound;
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct menu *menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void menu_run(struct menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void menu_delete(struct menu *menu);

#endif
