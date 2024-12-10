#include "application.h"
#include "gameplay.h"
#include "menu.h"
#include "sdl2.h"
#include <stdio.h>
#include <SDL_mixer.h>

struct application *application_initialize() {
    struct application *application;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return NULL;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!");
    }
    application = malloc(sizeof(struct application));
    application->window = SDL_CreateWindow("Maze",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (application->window == NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    application->renderer = SDL_CreateRenderer(application->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (application->renderer == NULL) {
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fprintf(stderr, "SDL_image failed to initialize: %s\n", IMG_GetError());
        return NULL;
    }
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer failed to initialize: %s\n", Mix_GetError());
        return NULL;
    }

    // Load menu music
    application->menu_music = Mix_LoadMUS("../assets/courtesy.mp3");
    if (!application->menu_music) {
        fprintf(stderr, "Failed to load menu music: %s\n", Mix_GetError());
        return NULL;
    }


    application->gameplay_music = Mix_LoadMUS("../assets/courtesy.mp3");
    if (!application->gameplay_music) {
        fprintf(stderr, "Failed to load gameplay music: %s\n", Mix_GetError());
        return NULL;
    }


    application->menu = menu_initialize(application->renderer);
    if (application->menu == NULL) {
        fprintf(stderr, "Failed to initialize menu: %s\n", IMG_GetError());
        return NULL;
    }
    application->gameplay = gameplay_initialize(application->renderer);
    if (application->gameplay == NULL) {
        fprintf(stderr, "Failed to initialize gameplay...\n");
        return NULL; // Make sure this exits initialization gracefully
    }

    application->state = APPLICATION_STATE_MENU;
    return application;
}


void application_run(struct application *application) {
    while (application->state != APPLICATION_STATE_QUIT) {
        switch (application->state) {
            case APPLICATION_STATE_MENU:
                if (Mix_PlayingMusic() == 0) {
		    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
                    Mix_PlayMusic(application->menu_music, -1);
                }
                menu_run(application->menu);
                if (application->menu->state == MENU_QUIT) {
                    application->state = APPLICATION_STATE_QUIT;
                } else if (application->menu->state == MENU_PLAY) {
		    application->state = APPLICATION_STATE_PLAY;
                    Mix_HaltMusic();
                }
                break;

            case APPLICATION_STATE_PLAY:
                if (application->gameplay == NULL) {
                    application->gameplay = gameplay_initialize(application->renderer);
                }
                if (Mix_PlayingMusic() == 0) {
                    Mix_PlayMusic(application->gameplay_music, -1);
                    Mix_VolumeMusic(MIX_MAX_VOLUME);
                }
                gameplay_run(application->gameplay, application->menu);

                if (application->menu->state == MENU_STATE) {
                    application->state = APPLICATION_STATE_MENU;

                // Cleanup gameplay state to prepare for a new game
                gameplay_cleanup(application->gameplay);
                application->gameplay = NULL;

                Mix_PlayMusic(application->menu_music, -1);
                Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
                }
                break;

            case APPLICATION_STATE_QUIT:
                break;
        }
    }
}



void application_shut_down(struct application *application) {
    Mix_FreeMusic(application->menu_music);
    Mix_FreeMusic(application->gameplay_music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    menu_delete(application->menu);
    free(application);
    application = NULL;
    IMG_Quit();
    SDL_Quit();
}

