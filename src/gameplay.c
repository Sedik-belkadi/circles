#include "constants.h"
#include "gameplay.h"
#include "spritesheet.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>


// Function prototype for calculate_angle
float calculate_angle(int mouse_x, int mouse_y, int center_x, int center_y) {
    return atan2(mouse_y - center_y, mouse_x - center_x); // Calculate angle
}

// Function to initialize the gameplay
Gameplay* gameplay_initialize(SDL_Renderer* renderer) {
    Gameplay* gameplay = malloc(sizeof(Gameplay));
    gameplay->renderer = renderer;
    gameplay->center_x = SCREEN_WIDTH / 2;  // Set the initial center position
    gameplay->center_y = SCREEN_HEIGHT / 2; // Set the initial center position
    gameplay->is_running = 1;  // Set the game to running state
    return gameplay;
}

// Function to run the game loop
void gameplay_run(Gameplay* gameplay) {
    SDL_Event event;
    int mouse_x, mouse_y;

    // Get the current mouse position
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // Calculate the angle of the triangle based on mouse position
    float angle = calculate_angle(mouse_x, mouse_y, gameplay->center_x, gameplay->center_y);

    // Clear the screen with blue background
    SDL_SetRenderDrawColor(gameplay->renderer, 0, 0, 255, 255); // Blue background color
    SDL_RenderClear(gameplay->renderer);

    // Draw the background circle first
    gameplay_draw_circle(gameplay);

    // Render the triangle on top (rotated based on mouse position)
    render_triangle(gameplay->renderer, gameplay->center_x, gameplay->center_y, angle);

    // Present the rendered frame
    SDL_RenderPresent(gameplay->renderer);

    // Handle SDL events (quit, etc.)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameplay->is_running = 0; // Stop the game
        }
    }
}

// Function to render the triangle
void render_triangle(SDL_Renderer* renderer, int center_x, int center_y, float angle) {
    // Set the color of the triangle (Red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color

    // Calculate triangle points based on angle
    const int size = 30;  // Adjust triangle size to be smaller
    SDL_Point points[3];

    points[0].x = center_x + size * cos(angle);     // Right point
    points[0].y = center_y + size * sin(angle);

    points[1].x = center_x + size * cos(angle + M_PI * 2 / 3);  // Left upper point
    points[1].y = center_y + size * sin(angle + M_PI * 2 / 3);

    points[2].x = center_x + size * cos(angle - M_PI * 2 / 3);  // Left lower point
    points[2].y = center_y + size * sin(angle - M_PI * 2 / 3);

    // Render the triangle using SDL
    SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
    SDL_RenderDrawLine(renderer, points[1].x, points[1].y, points[2].x, points[2].y);
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x, points[0].y);
}

// Function to render the background circle
void gameplay_draw_circle(Gameplay* gameplay) {
    int radius = 50;  // Adjust the size as needed

    // Loop to draw the circle (we're drawing pixels here)
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;  // horizontal offset
            int dy = radius - h;  // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(gameplay->renderer, gameplay->center_x + dx, gameplay->center_y + dy);
            }
        }
    }
}

