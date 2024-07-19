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
    SDL_Renderer *renderer;        ///< The SDL renderer used for drawing shapes.
    std::vector<Shape *> shapes;   ///< Collection of shapes to be drawn.
    int offset_x = 0;              ///< X offset for drawing.
    int offset_y = 0;              ///< Y offset for drawing.
    int start_pan_x = 0;           ///< Starting x-coordinate for panning.
    int start_pan_y = 0;           ///< Starting y-coordinate for panning.
    double scale = 1.0;            ///< Scale factor for drawing.
    double zoom_in_factor = 1.05;  ///< Zoom in factor.
    double zoom_out_factor = 0.95; ///< Zoom out factor.

public:
    /**
     * @brief Constructor to initialize the screen with a renderer.
     * @param renderer The SDL renderer.
     */
    explicit Screen(SDL_Renderer *renderer) : renderer(renderer) {}

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

    /**
     * @brief Sets the point where the user started panning.
     * @param mouse_x The x-coordinate of the mouse.
     * @param mouse_y The y-coordinate of the mouse.
     */
    void setPanStart(int mouse_x, int mouse_y)
    {
        start_pan_x = mouse_x;
        start_pan_y = mouse_y;
    }

    /**
     * @brief Pans the screen based on the mouse movement.
     * @param mouse_x The x-coordinate of the mouse.
     * @param mouse_y The y-coordinate of the mouse.
     */
    void pan(int mouse_x, int mouse_y)
    {
        // Increase or decrease the offset based on the mouse movement.
        offset_x += static_cast<int>((mouse_x - start_pan_x) / scale);
        offset_y += static_cast<int>((mouse_y - start_pan_y) / scale);

        // Reset the starting point for the next pan operation.
        start_pan_x = mouse_x;
        start_pan_y = mouse_y;
    }

    /**
     * @brief Zooms in on the screen.
     * @param mouse_x The x-coordinate of the mouse.
     * @param mouse_y The y-coordinate of the mouse.
     */
    void zoomIn(int mouse_x, int mouse_y)
    {
        // Adjust scale factor for zooming in
        scale *= zoom_in_factor;

        // Calculate the displacement caused by zooming in
        int dx = static_cast<int>(mouse_x * (zoom_in_factor - 1) / scale);
        int dy = static_cast<int>(mouse_y * (zoom_in_factor - 1) / scale);

        // Adjust the offset based on the displacement
        offset_x -= dx;
        offset_y -= dy;
    }

    /**
     * @brief Zooms out on the screen.
     * @param mouse_x The x-coordinate of the mouse.
     * @param mouse_y The y-coordinate of the mouse.
     */
    void zoomOut(int mouse_x, int mouse_y)
    {
        // Adjust scale factor for zooming out
        scale *= zoom_out_factor;

        // Calculate the displacement caused by zooming out
        int dx = static_cast<int>(mouse_x * (zoom_out_factor - 1) / scale);
        int dy = static_cast<int>(mouse_y * (zoom_out_factor - 1) / scale);

        // Adjust the offset based on the displacement
        offset_x -= dx;
        offset_y -= dy;
    }

    /**
     * @brief Speeds up the rotation of all shapes on the screen.
     */
    void speedUp()
    {
        for (Shape *shape : shapes)
        {
            shape->speedUp();
        }
    }

    /**
     * @brief Slows down the rotation of all shapes on the screen.
     */
    void slowDown()
    {
        for (Shape *shape : shapes)
        {
            shape->slowDown();
        }
    }
};

#endif // SCREEN_HPP
