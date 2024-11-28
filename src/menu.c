#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>

struct menu *menu_initialize(SDL_Renderer *renderer) {
    struct menu *menu;
    menu = malloc(sizeof(struct menu));
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
                        // Cycle difficulty options left
                        if (menu->state == MENU_EASY_FOCUS) {
                            menu->state = MENU_HARD_FOCUS;
                        } else if (menu->state == MENU_MEDIUM_FOCUS) {
                            menu->state = MENU_EASY_FOCUS;
                        } else if (menu->state == MENU_HARD_FOCUS) {
                            menu->state = MENU_MEDIUM_FOCUS;
                        }
                        break;
                    case SDLK_RIGHT:
                        // Cycle difficulty options right
                        if (menu->state == MENU_EASY_FOCUS) {
                            menu->state = MENU_MEDIUM_FOCUS;
                        } else if (menu->state == MENU_MEDIUM_FOCUS) {
                            menu->state = MENU_HARD_FOCUS;
                        } else if (menu->state == MENU_HARD_FOCUS) {
                            menu->state = MENU_EASY_FOCUS;
                        }
                        break;
                    case SDLK_RETURN:
                        if (menu->state == MENU_PLAY_FOCUS) {
                            menu->state = MENU_PLAY;
                        } else if (menu->state == MENU_QUIT_FOCUS) {
                            menu->state = MENU_QUIT;
                        }
                        break;
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

        // Render difficulty options, highlight the selected one
        if (menu->state == MENU_EASY_FOCUS) {
            spritesheet_render(menu->easy, EASY_X, EASY_Y, 255, 0);  // Highlighted
            spritesheet_render(menu->medium, MEDIUM_X, MEDIUM_Y, 64, 0);  // Dimmed
            spritesheet_render(menu->hard, HARD_X, HARD_Y, 64, 0);  // Dimmed
        } else if (menu->state == MENU_MEDIUM_FOCUS) {
            spritesheet_render(menu->easy, EASY_X, EASY_Y, 64, 0);  // Dimmed
            spritesheet_render(menu->medium, MEDIUM_X, MEDIUM_Y, 255, 0);  // Highlighted
            spritesheet_render(menu->hard, HARD_X, HARD_Y, 64, 0);  // Dimmed
        } else if (menu->state == MENU_HARD_FOCUS) {
            spritesheet_render(menu->easy, EASY_X, EASY_Y, 64, 0);  // Dimmed
            spritesheet_render(menu->medium, MEDIUM_X, MEDIUM_Y, 64, 0);  // Dimmed
            spritesheet_render(menu->hard, HARD_X, HARD_Y, 255, 0);  // Highlighted
        }

        // Render the difficulty button itself (at the bottom)
        spritesheet_render(menu->difficulty, DIFFICULTY_X, DIFFICULTY_Y, 255, 0);

        SDL_RenderPresent(menu->renderer);
    }
}
//test8




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

