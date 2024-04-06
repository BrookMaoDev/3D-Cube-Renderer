/**
 * @author Brook Mao
 * @date March 23, 2024
 * @details 3D Graphics Renderer
 */

#include <stdio.h>
#include "SDL.h"
#include "cube.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int WINDOW_CENTER_X = SCREEN_WIDTH / 2;
const int WINDOW_CENTER_Y = SCREEN_HEIGHT / 2;
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;
int cube_width = 200;
int cube_center_x;
int cube_center_y;
int shift = 5;
double theta = 0.01;
double delta_theta = 0.001;

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowTitle(window, "3D Graphics Engine");

    Cube cube(WINDOW_CENTER_X, WINDOW_CENTER_Y, cube_width);

    SDL_Event e;
    bool quit = false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_w)
                {
                    cube.shift_up(shift);
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                    cube.shift_left(shift);
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    cube.shift_up(-shift);
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
                    cube.shift_left(-shift);
                }

                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    theta += delta_theta;
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    theta -= delta_theta;
                }
            }

            if (e.type == SDL_MOUSEWHEEL)
            {
                if (e.wheel.y > 0)
                {
                    cube.zoom_in();
                }
                else if (e.wheel.y < 0)
                {
                    cube.zoom_out();
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        cube.draw_cube(renderer);
        cube.rotate_cube(theta);

        SDL_Delay(DELAY_TIME);
    }
}
