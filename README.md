# Circles

**English** | [Français](README.fr.md)

Circles is a C game inspired by *Super Hexagon*, developed as part of a C programming course project. The player guides a triangle around the center of the arena while avoiding approaching obstacles.

## Features

- Menu with three difficulty levels
- Mouse-controlled player movement
- Moving obstacles and collision detection
- Survival timer
- Game-over screen and sound effect
- Music and sound effects

## Technologies

- C
- SDL2 for the window, rendering, and events
- SDL2_image for loading images
- SDL2_mixer for music and sound effects
- SDL2_gfx for drawing shapes

## Build and run

The project was developed and tested on Ubuntu 22.04. It requires GCC, Make, `sdl2-config`, and the SDL2 development libraries listed above.

On Ubuntu, install the dependencies with:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-gfx-dev
```

From the repository root, build and run the game from the `src` directory:

```bash
cd src
make
./circles
```

The executable loads assets from `../assets`, so run it from `src` for the asset paths to resolve correctly.

## Controls

- In the menu, move the mouse to navigate the options. Click a difficulty, then click **Play** to start.
- During gameplay, move the mouse around the center of the window to steer the triangle.
- Click **Quit** to close the game.

## Author

Mohammed Essedik Belkadi  
Completed individually as assignment 3 for the C programming course.

## References

Official documentation for the SDL2 libraries used in this project.
