#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>
#include <stdlib.h> // Added for malloc and free

struct menu *menu_initialize(SDL_Renderer *renderer) {
    struct menu *menu;
    menu = malloc(sizeof(struct menu));
    if (menu == NULL) {
        fprintf(stderr, "Failed to allocate memory for menu\n");
        return NULL;
    }
    menu->renderer = renderer;
    menu->state = MENU_EASY_FOCUS;
    menu->background = spritesheet_create(BACKGROUND_FILENAME, 1, 1, 1, renderer);
    menu->title = spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->play = spritesheet_create(PLAY_FILENAME, 1, 1, 1, renderer);
    menu->quit = spritesheet_create(QUIT_FILENAME, 1, 1, 1, renderer);
    menu->difficulty = spritesheet_create(DIFFICULTY_FILENAME, 1, 1, 1, renderer);
    menu->easy = spritesheet_create(EASY_FILENAME, 1, 1, 1, renderer);
    menu->medium = spritesheet_create(MEDIUM_FILENAME, 1, 1, 1, renderer);
    menu->hard = spritesheet_create(HARD_FILENAME, 1, 1, 1, renderer);
    return menu;
}

int menu_alpha(bool chosen) {
    return chosen ? 255 : 64;
}

void menu_run(struct menu *menu) {
    SDL_Event e;
    while (menu->state != MENU_PLAY && menu->state != MENU_QUIT) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                menu->state = MENU_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        menu->state = (menu->state == MENU_EASY_FOCUS) ? MENU_HARD_FOCUS
                                    : (menu->state == MENU_MEDIUM_FOCUS) ? MENU_EASY_FOCUS
                                    : MENU_MEDIUM_FOCUS;
                        break;
                    case SDLK_RIGHT:
                        menu->state = (menu->state == MENU_EASY_FOCUS) ? MENU_MEDIUM_FOCUS
                                    : (menu->state == MENU_MEDIUM_FOCUS) ? MENU_HARD_FOCUS
                                    : MENU_EASY_FOCUS;
                        break;
                    case SDLK_RETURN:
                        if (menu->state == MENU_PLAY_FOCUS) menu->state = MENU_PLAY;
                        else if (menu->state == MENU_QUIT_FOCUS) menu->state = MENU_QUIT;
                        break;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                int mouse_x = e.motion.x;
                int mouse_y = e.motion.y;

                // Check hover over Play button
                if (mouse_x >= PLAY_X - 60 && mouse_x <= PLAY_X + PLAY_WIDTH + 60 &&
                    mouse_y >= PLAY_Y - 60 && mouse_y <= PLAY_Y + PLAY_HEIGHT + 60) {
                    menu->state = MENU_PLAY_FOCUS;
                }
                // Check hover over Quit button
                else if (mouse_x >= QUIT_X - 60 && mouse_x <= QUIT_X + QUIT_WIDTH + 60 &&
                         mouse_y >= QUIT_Y - 60 && mouse_y <= QUIT_Y + QUIT_HEIGHT + 60) {
                    menu->state = MENU_QUIT_FOCUS;
                }
                // Check hover over difficulty options
                else if (mouse_x >= EASY_X - 10 && mouse_x <= EASY_X + EASY_WIDTH + 10 &&
                         mouse_y >= EASY_Y - 10 && mouse_y <= EASY_Y + EASY_HEIGHT + 10) {
                    menu->state = MENU_EASY_FOCUS;

                } else if (mouse_x >= MEDIUM_X - 10 && mouse_x <= MEDIUM_X + MEDIUM_WIDTH + 10 &&
                           mouse_y >= MEDIUM_Y - 10 && mouse_y <= MEDIUM_Y + MEDIUM_HEIGHT + 10) {
                    menu->state = MENU_MEDIUM_FOCUS;
                } else if (mouse_x >= HARD_X - 10 && mouse_x <= HARD_X + HARD_WIDTH + 10 &&
                           mouse_y >= HARD_Y - 10 && mouse_y <= HARD_Y + HARD_HEIGHT + 10) {
                    menu->state = MENU_HARD_FOCUS;
                }
            }
	      else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Check for left mouse click
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouse_x = e.button.x;
                    int mouse_y = e.button.y;

                    // Check if the click is inside the "Play" button
                    if (mouse_x >= PLAY_X - 60 && mouse_x <= PLAY_X + PLAY_WIDTH + 60 &&
                        mouse_y >= PLAY_Y - 60 && mouse_y <= PLAY_Y + PLAY_HEIGHT + 60) {
                        menu->state = MENU_PLAY;
                    }

                    // Check if the click is inside the "Quit" button
                    else if (mouse_x >= QUIT_X - 60 && mouse_x <= QUIT_X + QUIT_WIDTH + 60 &&
                             mouse_y >= QUIT_Y - 60 && mouse_y <= QUIT_Y + QUIT_HEIGHT + 60) {
                        menu->state = MENU_QUIT;
                    }
                }
            }
	}

        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(menu->renderer);

        // Render background and title
        spritesheet_render(menu->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
        spritesheet_render(menu->title, TITLE_X, TITLE_Y, 255, 0);

        // Render Play and Quit options
        spritesheet_render(menu->play, PLAY_X, PLAY_Y, menu_alpha(menu->state == MENU_PLAY_FOCUS), 0);
        spritesheet_render(menu->quit, QUIT_X, QUIT_Y, menu_alpha(menu->state == MENU_QUIT_FOCUS), 0);

        // Render difficulty options
        spritesheet_render(menu->easy, EASY_X, EASY_Y, menu_alpha(menu->state == MENU_EASY_FOCUS), 0);
        spritesheet_render(menu->medium, MEDIUM_X, MEDIUM_Y, menu_alpha(menu->state == MENU_MEDIUM_FOCUS), 0);
        spritesheet_render(menu->hard, HARD_X, HARD_Y, menu_alpha(menu->state == MENU_HARD_FOCUS), 0);

        // Render the difficulty button
        spritesheet_render(menu->difficulty, DIFFICULTY_X, DIFFICULTY_Y, 255, 0);

        SDL_RenderPresent(menu->renderer);
    }
}

void menu_delete(struct menu *menu) {
    if (menu != NULL) {
        spritesheet_delete(menu->background);
        spritesheet_delete(menu->title);
        spritesheet_delete(menu->play);
        spritesheet_delete(menu->quit);
        spritesheet_delete(menu->difficulty);
        spritesheet_delete(menu->easy);
        spritesheet_delete(menu->medium);
        spritesheet_delete(menu->hard);
        free(menu);
    }
}

