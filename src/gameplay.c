#include "constants.h"
#include "gameplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

// Function prototype for calculate_angle
float calculate_angle(int mouse_x, int mouse_y, int center_x, int center_y) {
    return atan2(mouse_y - center_y, mouse_x - center_x);
}

// Function to initialize the gameplay
Gameplay* gameplay_initialize(SDL_Renderer* renderer) {
    Gameplay* gameplay = malloc(sizeof(Gameplay));
    gameplay->renderer = renderer;
    gameplay->center_x = SCREEN_WIDTH / 2;
    gameplay->center_y = SCREEN_HEIGHT / 2;
    gameplay->is_running = 1;
    return gameplay;
}

// Function to run the game loop
void gameplay_run(Gameplay* gameplay) {
    SDL_Event event;
    int mouse_x, mouse_y;

    while (gameplay->is_running) {
        // Get the current mouse position
        SDL_GetMouseState(&mouse_x, &mouse_y);

        // Calculate the angle of the triangle based on mouse position
        float angle = calculate_angle(mouse_x, mouse_y, gameplay->center_x, gameplay->center_y);

        // Clear the screen
        SDL_SetRenderDrawColor(gameplay->renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(gameplay->renderer);

        // Draw the alternating radial background
        gameplay_draw_background(gameplay);

        // Draw the central circle
        filledCircleRGBA(gameplay->renderer, gameplay->center_x, gameplay->center_y, 40, 128, 128, 128, 255);

        // Render the triangle moving around the circle
        render_triangle(gameplay->renderer, gameplay->center_x, gameplay->center_y, angle, 67);

        // Present the rendered frame
        SDL_RenderPresent(gameplay->renderer);

        // Handle SDL events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameplay->is_running = 0;
            }
        }
    }
}

// Function to render the triangle
void render_triangle(SDL_Renderer* renderer, int center_x, int center_y, float angle, int radius) {
    const int size = 20; // Triangle size
    Sint16 vx[3], vy[3];

    // Position the triangle around the edge of the circle
    int base_x = center_x + radius * cos(angle);
    int base_y = center_y + radius * sin(angle);

    angle += M_PI;

    // Define the vertices of the triangle
    vx[0] = base_x;
    vy[0] = base_y;

    vx[1] = base_x + size * cos(angle + M_PI / 6);
    vy[1] = base_y + size * sin(angle + M_PI / 6);

    vx[2] = base_x + size * cos(angle - M_PI / 6);
    vy[2] = base_y + size * sin(angle - M_PI / 6);

    filledPolygonRGBA(renderer, vx, vy, 3, 0, 0, 255, 255); // Blue triangle
}

// Function to draw the radial background
void gameplay_draw_background(Gameplay* gameplay) {
    const int num_slices = 6;
    const double slice_angle = 2 * M_PI / num_slices;

    for (int i = 0; i < num_slices; ++i) {
        double start_angle = i * slice_angle;
        double end_angle = start_angle + slice_angle;
        Uint8 color = (i % 2 == 0) ? 200 : 255; // Alternate grey and white

        for (int r = 0; r < SCREEN_HEIGHT; ++r) {
            for (double theta = start_angle; theta < end_angle; theta += 0.01) {
                int x = gameplay->center_x + r * cos(theta);
                int y = gameplay->center_y + r * sin(theta);
                if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
                    SDL_SetRenderDrawColor(gameplay->renderer, color, color, color, 255);
                    SDL_RenderDrawPoint(gameplay->renderer, x, y);
                }
            }
        }
    }
}

