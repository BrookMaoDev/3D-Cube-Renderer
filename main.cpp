/**
 * @author Brook Mao
 * @date March 23, 2024
 * @details 3D Graphics Renderer
 */

#include <stdio.h>
#include "SDL.h"
#include "cube.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WINDOW_CENTER_X = SCREEN_WIDTH / 2;
const int WINDOW_CENTER_Y = SCREEN_HEIGHT / 2;
const int CUBE_WIDTH = 200;
const int HALF_CUBE_WIDTH = CUBE_WIDTH / 2;

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowTitle(window, "3D Graphics Engine");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int cubeVertices[8][3] = {
        // Front face vertices
        {WINDOW_CENTER_X - HALF_CUBE_WIDTH, WINDOW_CENTER_Y - HALF_CUBE_WIDTH, 0}, // Bottom left front
        {WINDOW_CENTER_X + HALF_CUBE_WIDTH, WINDOW_CENTER_Y - HALF_CUBE_WIDTH, 0}, // Bottom right front
        {WINDOW_CENTER_X + HALF_CUBE_WIDTH, WINDOW_CENTER_Y + HALF_CUBE_WIDTH, 0}, // Top right front
        {WINDOW_CENTER_X - HALF_CUBE_WIDTH, WINDOW_CENTER_Y + HALF_CUBE_WIDTH, 0}, // Top left front
        // Back face vertices
        {WINDOW_CENTER_X - HALF_CUBE_WIDTH, WINDOW_CENTER_Y - HALF_CUBE_WIDTH, CUBE_WIDTH}, // Bottom left back
        {WINDOW_CENTER_X + HALF_CUBE_WIDTH, WINDOW_CENTER_Y - HALF_CUBE_WIDTH, CUBE_WIDTH}, // Bottom right back
        {WINDOW_CENTER_X + HALF_CUBE_WIDTH, WINDOW_CENTER_Y + HALF_CUBE_WIDTH, CUBE_WIDTH}, // Top right back
        {WINDOW_CENTER_X - HALF_CUBE_WIDTH, WINDOW_CENTER_Y + HALF_CUBE_WIDTH, CUBE_WIDTH}  // Top left back
    };
    Cube cube(cubeVertices);

    SDL_Event e;
    bool quit = false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        cube.draw_cube(renderer);
        SDL_RenderPresent(renderer);
    }
}
