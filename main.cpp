/**
 * @author Brook Mao
 * @date March 23, 2024
 * @brief Renders a rotating cube, allowing the user to control rotation speed, movement of the cube, and zoom.
 */

#include <stdio.h>
#include "SDL.h"
#include "cube.hpp"

int initial_screen_width = 640;
int initial_screen_height = 640;
int cube_width = 200;
int cube_center_x = initial_screen_width / 2;
int cube_center_y = initial_screen_height / 2;

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int shift = 5;              // Amount to move the cube by when the user wants to move the cube
double theta = 0.01;        // Amount to rotate by each time, can also be thought of as rate of rotation
double delta_theta = 0.001; // How much to increase/decrease rate of rotation when user wants to

int main(int argc, char *args[])
{
    // Start up SDL, the library allowing us to create a screen to draw on
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create our application window
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(640, 640, SDL_WINDOW_RESIZABLE, &window, &renderer);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowTitle(window, "3D Graphics Engine");

    // Create a cube object
    Cube cube(cube_center_x, cube_center_y, cube_width);

    SDL_Event e; // Helps us track user events such as scrolling, or pressing keys
    bool quit = false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            // Closes the window if prompted to by the user
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // Keyboard events
            if (e.type == SDL_KEYDOWN)
            {
                // Movement of the cube
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

                // Increase/decrease in rotation speed
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    theta += delta_theta;
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    theta -= delta_theta;
                }
            }

            // Mouse wheel events
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

        // Black out the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Draw the cube in white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        cube.draw_cube(renderer);

        // Rotate FPS times a second
        cube.rotate_cube(theta);
        SDL_Delay(DELAY_TIME);
    }
}
