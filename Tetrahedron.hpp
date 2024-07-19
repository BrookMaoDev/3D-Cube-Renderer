#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "Shape.hpp"

/**
 * @class Tetrahedron
 * @brief A class representing a 3D tetrahedron that can be rendered using SDL.
 */
class Tetrahedron : public Shape
{
public:
    /**
     * @brief Constructor to initialize the tetrahedron with a renderer, color, center position, and width.
     * @param renderer The SDL renderer.
     * @param color The color of the tetrahedron.
     * @param center_x The x-coordinate of the tetrahedron's center.
     * @param center_y The y-coordinate of the tetrahedron's center.
     * @param width The width of the tetrahedron.
     */
    Tetrahedron(SDL_Renderer *renderer, SDL_Color color, int center_x, int center_y, int width)
        : Shape(renderer, color, center_x, center_y)
    {
        // Initialize the tetrahedron's 3D points relative to the center
        int half_width = width / 2;
        pts_relative_to_center_3d.emplace_back(-half_width, half_width, -half_width); // Bottom left back
        pts_relative_to_center_3d.emplace_back(half_width, half_width, -half_width);  // Bottom right back
        pts_relative_to_center_3d.emplace_back(0, -half_width, 0);                    // Top
        pts_relative_to_center_3d.emplace_back(0, half_width, half_width);            // Front
    }

    /**
     * @brief Draws the tetrahedron on the screen.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    void draw(int offset_x, int offset_y, double scale) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        project();
        convertWorldPointsToScreen(offset_x, offset_y, scale);

        // Draw the base of the tetrahedron
        drawLine(pts_absolute_2d[0], pts_absolute_2d[1]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[3]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[0]);

        // Draw the sides of the tetrahedron
        drawLine(pts_absolute_2d[0], pts_absolute_2d[2]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[2]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[3]);
    }
};

#endif // TETRAHEDRON_HPP
