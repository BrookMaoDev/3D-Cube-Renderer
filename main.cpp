/**
 * @author Brook Mao
 * @date March 23, 2024
 * @details 3D Graphics Renderer
 */

#include <stdio.h>
#include "SDL.h"
#include "cube.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int WINDOW_CENTER_X = SCREEN_WIDTH / 2;
const int WINDOW_CENTER_Y = SCREEN_HEIGHT / 2;
const int CUBE_WIDTH = 100;
const int HALF_CUBE_WIDTH = CUBE_WIDTH / 2;
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

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

    Cube cube(WINDOW_CENTER_X, WINDOW_CENTER_Y, CUBE_WIDTH);

    SDL_Event e;
    bool quit = false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        cube.draw_cube(renderer);
        cube.rotate_cube();

        SDL_Delay(DELAY_TIME);
    }
}
