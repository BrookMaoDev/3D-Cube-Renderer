#ifndef SQUARE_BASED_PYRAMID_HPP
#define SQUARE_BASED_PYRAMID_HPP

#include "Shape.hpp"

/**
 * @class SquareBasedPyramid
 * @brief A class representing a 3D square-based pyramid that can be rendered using SDL.
 */
class SquareBasedPyramid : public Shape
{
public:
    /**
     * @brief Constructor to initialize the square-based pyramid with a renderer, color, center position, and width.
     * @param renderer The SDL renderer.
     * @param color The color of the square-based pyramid.
     * @param center_x The x-coordinate of the square-based pyramid's center.
     * @param center_y The y-coordinate of the square-based pyramid's center.
     * @param width The width of the square-based pyramid.
     */
    SquareBasedPyramid(SDL_Renderer *renderer, SDL_Color color, int center_x, int center_y, int width)
        : Shape(renderer, color, center_x, center_y)
    {
        // Initialize the square-based pyramid's 3D points relative to the center
        int half_width = width / 2;
        pts_relative_to_center_3d.push_back(Point(-half_width, half_width, -half_width)); // Bottom left back
        pts_relative_to_center_3d.push_back(Point(half_width, half_width, -half_width));  // Bottom right back
        pts_relative_to_center_3d.push_back(Point(-half_width, half_width, half_width));  // Bottom left front
        pts_relative_to_center_3d.push_back(Point(half_width, half_width, half_width));   // Bottom right front
        pts_relative_to_center_3d.push_back(Point(0, -half_width, 0));                    // Top
    }

    /**
     * @brief Draws the square-based pyramid on the screen.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    void draw(int offset_x, int offset_y, double scale) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        project();
        convertWorldPointsToScreen(offset_x, offset_y, scale);

        // Draw the base
        drawLine(pts_absolute_2d[0], pts_absolute_2d[1]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[3]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[2]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[0]);

        // Draw the sides
        drawLine(pts_absolute_2d[0], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[4]);
    }
};

#endif // SQUARE_BASED_PYRAMID_HPP
