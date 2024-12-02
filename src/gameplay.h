#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer* renderer;
    int is_running;
    int center_x, center_y;
} Gameplay;

float calculate_angle(int mouse_x, int mouse_y, int center_x, int center_y);
Gameplay* gameplay_initialize(SDL_Renderer* renderer);
void gameplay_run(Gameplay* gameplay);
void render_triangle(SDL_Renderer* renderer, int center_x, int center_y, float angle);
void gameplay_draw_circle(Gameplay* gameplay);

#endif

