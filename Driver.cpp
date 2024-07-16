#include "SDL.h"
#include "Screen.hpp"
#include "Cube.hpp"

const int FPS = 60;                        ///< Frames per second.
const int MILLISECONDS_DELAY = 1000 / FPS; ///< Delay per frame in milliseconds.
const int INITIAL_SCREEN_WIDTH = 800;      ///< Initial screen width.
const int INITIAL_SCREEN_HEIGHT = 600;     ///< Initial screen height.

/**
 * @brief Main function to initialize SDL, create a window and renderer, and run the rendering loop.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status code.
 */
int main(int argc, char *argv[])
{
    // Initialize SDL video subsystem
    SDL_Init(SDL_INIT_VIDEO);

    // Create an SDL window and renderer
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "3D Rendering Engine");

    // Create a screen and add shapes to it
    Screen screen(renderer);
    screen.addShape(new Cube(renderer, SDL_Color{255, 0, 0, 255}, INITIAL_SCREEN_WIDTH / 4, INITIAL_SCREEN_HEIGHT / 4, 200));
    screen.addShape(new Cube(renderer, SDL_Color{0, 255, 0, 255}, 3 * INITIAL_SCREEN_WIDTH / 4, 3 * INITIAL_SCREEN_HEIGHT / 4, 200));

    SDL_Event event;
    bool running = true;

    // Main rendering loop
    while (running)
    {
        // Handle SDL events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Clear the screen with a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set the default drawing color to white and draw the shapes
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        screen.draw();
        screen.rotate();

        // Present the renderer to the screen
        SDL_RenderPresent(renderer);

        // Delay to maintain the target FPS
        SDL_Delay(MILLISECONDS_DELAY);
    }

    // Clean up SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
