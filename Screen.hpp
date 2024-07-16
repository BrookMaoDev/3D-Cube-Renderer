#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "SDL.h"
#include "Shape.hpp"
#include <vector>

/**
 * @class Screen
 * @brief A class to manage and render multiple shapes using SDL.
 */
class Screen
{
private:
    SDL_Renderer *renderer;      ///< The SDL renderer used for drawing shapes.
    std::vector<Shape *> shapes; ///< Collection of shapes to be drawn.
    int offset_x = 0;            ///< X offset for drawing.
    int offset_y = 0;            ///< Y offset for drawing.
    double scale = 1.0;          ///< Scale factor for drawing.

public:
    /**
     * @brief Constructor to initialize the screen with a renderer.
     * @param renderer The SDL renderer.
     */
    Screen(SDL_Renderer *renderer) : renderer(renderer) {}

    /**
     * @brief Adds a shape to the screen and sets its renderer.
     * @param shape Pointer to the shape to be added.
     */
    void addShape(Shape *shape)
    {
        shapes.push_back(shape);
        shape->setRenderer(renderer);
    }

    /**
     * @brief Draws all shapes on the screen.
     */
    void draw()
    {
        for (Shape *shape : shapes)
        {
            shape->draw(offset_x, offset_y, scale);
        }
    }

    /**
     * @brief Rotates all shapes on the screen.
     */
    void rotate()
    {
        for (Shape *shape : shapes)
        {
            shape->rotate();
        }
    }
};

#endif // SCREEN_HPP
