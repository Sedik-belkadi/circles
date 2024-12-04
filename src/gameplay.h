#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL2/SDL.h>
#include <math.h>

typedef struct {
    float angle;   // Angle of the obstacle
    float distance;  // Distance from the center
    int appear_time;
    int reappearance_time;
} Obstacle;

typedef struct {
    SDL_Renderer* renderer;
    int is_running;
    int center_x, center_y;
    Obstacle* obstacles;
} Gameplay;


float calculate_angle(int mouse_x, int mouse_y, int center_x, int center_y);
Gameplay* gameplay_initialize(SDL_Renderer* renderer);
void gameplay_run(Gameplay* gameplay);
void render_triangle(SDL_Renderer* renderer, int center_x, int center_y, float angle, int radius);
void gameplay_draw_circle(Gameplay* gameplay);
void gameplay_draw_background(Gameplay* gameplay);
void move_obstacles(Gameplay* gameplay);
void render_obstacles(Gameplay* gameplay);

#endif

