#include "constants.h"
#include "gameplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// Function to calculate angle between the mouse and center
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

    // Initialize obstacles
    gameplay->obstacles = malloc(sizeof(Obstacle) * 6);
    for (int i = 0; i < 6; i++) {
        gameplay->obstacles[i].angle = i * 2 * M_PI / 6;  // Evenly spaced angles
        gameplay->obstacles[i].distance = SCREEN_HEIGHT * 0.8; // Start near the screen edges
        gameplay->obstacles[i].appear_time = rand() % 100 + 1; // Random delay for obstacle appearance
        gameplay->obstacles[i].reappearance_time = (i + 1) * 10 + (rand() % 10); // Initially no delay for reappearance
    }

    return gameplay;
}

// Function to run the game loop
void gameplay_run(Gameplay* gameplay, struct menu *menu) {
    SDL_Event event;
    int mouse_x, mouse_y;

    while (gameplay->is_running) {
        SDL_GetMouseState(&mouse_x, &mouse_y);
        float angle = calculate_angle(mouse_x, mouse_y, gameplay->center_x, gameplay->center_y);

        // Clear the screen
        SDL_SetRenderDrawColor(gameplay->renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(gameplay->renderer);

        // Draw the alternating radial background
        gameplay_draw_background(gameplay);

        // Draw the central circle
        filledCircleRGBA(gameplay->renderer, gameplay->center_x, gameplay->center_y, 40, 128, 128, 128, 255);

        // Render the obstacles
        render_obstacles(gameplay);

        // Render the triangle moving around the circle
        render_triangle(gameplay->renderer, gameplay->center_x, gameplay->center_y, angle, 67);

        // Present the rendered frame
        SDL_RenderPresent(gameplay->renderer);

        // Handle SDL events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameplay->is_running = 0; // End game
            }
        }

        // Move obstacles closer to the center
        move_obstacles(gameplay);

        if (check_collision(gameplay, angle)) {
            gameplay->is_running = 0; // Set game over condition
	    display_game_over(gameplay->renderer);
	    menu->state = MENU_STATE;
        }
    }
}


// Function to render the obstacles
void render_obstacles(Gameplay* gameplay) {
    for (int i = 0; i < 6; i++) {
        if (gameplay->obstacles[i].reappearance_time > 0) {
            continue; // Skip rendering if still in delay
        }

        float distance = gameplay->obstacles[i].distance;

        if (distance < 40) {
            continue;  // Skip rendering if too close to the center
        }

        // Ensure the obstacle's angle is aligned with the slice
        float slice_angle = 2 * M_PI / 6; // 6 slices (in radians)

        // Align angle to the left edge of the slice
        float aligned_angle = (i * slice_angle) - (slice_angle / 18) - 1;

        // Define the angular bounds of the slice (start and end angles)
        float start_angle = aligned_angle;
        float end_angle = aligned_angle + slice_angle;

        // Render a precise thick arc for the obstacle (aligned with the slice)
        for (int thickness = 0; thickness < 10; thickness++) {
            arcRGBA(
                gameplay->renderer,
                gameplay->center_x,
                gameplay->center_y,
                (Sint16)(distance - thickness),
                (Sint16)((start_angle * 180.0) / M_PI),
                (Sint16)((end_angle * 180.0) / M_PI),
                255, 0, 0, 255 // Red arc
            );
        }
    }
}



// Function to move the obstacles towards the center
void move_obstacles(Gameplay* gameplay) {
    const float reset_distance = SCREEN_HEIGHT * 0.8; // Reset distance when obstacles reappear
    const float speed = 9.0; // Movement speed

    for (int i = 0; i < 6; i++) {
        // If obstacle is waiting to reappear
        if (gameplay->obstacles[i].reappearance_time > 0) {
            gameplay->obstacles[i].reappearance_time--; // Countdown for reappearance
            continue; // Skip further processing until it's time to reappear
        }

        // Move the obstacle
        if (gameplay->obstacles[i].distance > 40) {
            gameplay->obstacles[i].distance -= speed; // Move obstacle closer
        } else {
            // Reset obstacle to maximum distance when it disappears
            gameplay->obstacles[i].distance = reset_distance;

            // Assign a new random delay under 1 second for reappearance
            gameplay->obstacles[i].reappearance_time = rand() % 60; // Max 1 second at 60 FPS
        }

        // Align obstacle with its corresponding slice
        gameplay->obstacles[i].angle = i * 2 * M_PI / 6; // Evenly spaced angles (aligned with slices)
    }
}

// Function to check collision between the triangle and obstacles
int check_collision(Gameplay* gameplay, float triangle_angle) {
    for (int i = 0; i < 6; i++) {
        float obstacle_angle = gameplay->obstacles[i].angle;
        float distance = gameplay->obstacles[i].distance;

        // Check if the triangle is within the obstacle's bounds
        float slice_angle = 2 * M_PI / 6;
        float start_angle = obstacle_angle - slice_angle / 2;
        float end_angle = obstacle_angle + slice_angle / 2;

        if (distance <= 67 && triangle_angle >= start_angle && triangle_angle <= end_angle) {
            return 1; // Collision detected
        }
    }
    return 0;
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

void display_game_over(SDL_Renderer* renderer) {
    // Load the PNG image
    SDL_Surface* surface = IMG_Load("../assets/game_over.png");
    if (!surface) {
        fprintf(stderr, "Failed to load game over image: %s\n", IMG_GetError());
        return;
    }

    Mix_Chunk *game_over_sound = Mix_LoadWAV("../assets/game over.wav");
    if (game_over_sound == NULL) {
        printf("Failed to load game over sound! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Stop the background music
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }

    // Play the game over sound
    if (game_over_sound != NULL) {
        Mix_PlayChannel(-1, game_over_sound, 0); // Play sound once on the first available channel
    }

    // Convert the surface to a texture for rendering
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Free the surface as it's no longer needed

    if (!texture) {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        return;
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Get texture dimensions
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

    // Define the destination rectangle to center the image
    SDL_Rect dest_rect = {
        .x = (SCREEN_WIDTH - texture_width) / 2,
        .y = (SCREEN_HEIGHT - texture_height) / 2,
        .w = texture_width,
        .h = texture_height
    };

    // Render the texture
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer); // Present the renderer

    SDL_Delay(2000); // Display the game over image for 2 seconds

    SDL_DestroyTexture(texture); // Clean up the texture
}






