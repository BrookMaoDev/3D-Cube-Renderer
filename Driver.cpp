#include "SDL.h"
#include "Screen.hpp"
#include "Cube.hpp"
#include "Tetrahedron.hpp"
#include "Octahedron.hpp"
#include "SquareBasedPyramid.hpp"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()

const int FPS = 100;                       ///< Frames per second.
const int MILLISECONDS_DELAY = 1000 / FPS; ///< Delay per frame in milliseconds.
const int INITIAL_SCREEN_WIDTH = 800;      ///< Initial screen width.
const int INITIAL_SCREEN_HEIGHT = 600;     ///< Initial screen height;

/**
 * @brief Generates a random color.
 * @return A random color.
 */
SDL_Color getRandomColor()
{
    const int minBrightness = 128; // Minimum value to ensure color visibility on black
    const int maxBrightness = 255;

    SDL_Color color;
    color.r = minBrightness + (std::rand() % (maxBrightness - minBrightness + 1));
    color.g = minBrightness + (std::rand() % (maxBrightness - minBrightness + 1));
    color.b = minBrightness + (std::rand() % (maxBrightness - minBrightness + 1));
    color.a = 255; // Opaque

    return color;
}

/**
 * @brief Main function to initialize SDL, create a window and renderer, and run the rendering loop.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status code.
 */
int main(int argc, char *argv[])
{
    // Initialize random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create an SDL window and renderer
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer) != 0)
    {
        SDL_Log("Failed to create window or renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *icon = SDL_LoadBMP("icon.bmp");
    if (icon != nullptr)
    {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }
    SDL_SetWindowTitle(window, "3D Rendering Engine");

    // Create a screen and add shapes to it
    Screen screen(renderer);
    screen.addShape(new Cube(renderer, getRandomColor(), INITIAL_SCREEN_WIDTH / 4, INITIAL_SCREEN_HEIGHT / 4, 150));
    screen.addShape(new Tetrahedron(renderer, getRandomColor(), 3 * INITIAL_SCREEN_WIDTH / 4, INITIAL_SCREEN_HEIGHT / 4, 150));
    screen.addShape(new Octahedron(renderer, getRandomColor(), INITIAL_SCREEN_WIDTH / 4, 3 * INITIAL_SCREEN_HEIGHT / 4, 150));
    screen.addShape(new SquareBasedPyramid(renderer, getRandomColor(), 3 * INITIAL_SCREEN_WIDTH / 4, 3 * INITIAL_SCREEN_HEIGHT / 4, 150));

    SDL_Event event;
    bool running = true;
    bool mouse_down = false;
    bool paused = false;

    // Main rendering loop
    while (running)
    {
        // Handle SDL events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_down = true;
                screen.setPanStart(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_down = false;
                break;
            case SDL_MOUSEWHEEL:
            {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);

                if (event.wheel.y > 0)
                {
                    screen.zoomIn(mouse_x, mouse_y);
                }
                else if (event.wheel.y < 0)
                {
                    screen.zoomOut(mouse_x, mouse_y);
                }
            }
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    screen.slowDown();
                    break;
                case SDLK_RIGHT:
                    screen.speedUp();
                    break;
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                }
                break;
            default:
                if (mouse_down)
                {
                    screen.pan(event.button.x, event.button.y);
                }
                break;
            }
        }

        // Clear the screen with a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set the default drawing color to white and draw the shapes
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        screen.draw();

        // Rotate the shapes if not paused
        if (!paused)
        {
            screen.rotate();
        }

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
