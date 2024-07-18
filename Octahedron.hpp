#ifndef OCTAHEDRON_HPP
#define OCTAHEDRON_HPP

#include "Shape.hpp"

/**
 * @class Octahedron
 * @brief A class representing a 3D octahedron that can be rendered using SDL.
 */
class Octahedron : public Shape
{
public:
    /**
     * @brief Constructor to initialize the octahedron with a renderer, color, center position, and width.
     * @param renderer The SDL renderer.
     * @param color The color of the octahedron.
     * @param center_x The x-coordinate of the octahedron's center.
     * @param center_y The y-coordinate of the octahedron's center.
     * @param width The width of the octahedron.
     */
    Octahedron(SDL_Renderer *renderer, SDL_Color color, int center_x, int center_y, int width)
        : Shape(renderer, color, center_x, center_y)
    {
        // Initialize the octahedron's 3D points relative to the center
        int half_width = width / 2;
        pts_relative_to_center_3d.push_back(Point(0, -half_width, 0)); // Bottom
        pts_relative_to_center_3d.push_back(Point(half_width, 0, 0));  // Right
        pts_relative_to_center_3d.push_back(Point(0, half_width, 0));  // Top
        pts_relative_to_center_3d.push_back(Point(-half_width, 0, 0)); // Left
        pts_relative_to_center_3d.push_back(Point(0, 0, -half_width)); // Back
        pts_relative_to_center_3d.push_back(Point(0, 0, half_width));  // Front
    }

    /**
     * @brief Draws the octahedron on the screen.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    void draw(int offset_x, int offset_y, double scale) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        project();
        convertWorldPointsToScreen(offset_x, offset_y, scale);

        // Draw square center
        drawLine(pts_absolute_2d[0], pts_absolute_2d[1]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[2]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[3]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[0]);

        // Draw connections to the bottom
        drawLine(pts_absolute_2d[0], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[4]);

        // Draw connections to the top
        drawLine(pts_absolute_2d[0], pts_absolute_2d[5]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[5]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[5]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[5]);
    }
};

#endif // OCTAHEDRON_HPP
