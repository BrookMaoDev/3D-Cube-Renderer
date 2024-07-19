#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shape.hpp"

/**
 * @class Cube
 * @brief A class representing a 3D cube that can be rendered using SDL.
 */
class Cube : public Shape
{
public:
    /**
     * @brief Constructor to initialize the cube with a renderer, color, center position, and width.
     * @param renderer The SDL renderer.
     * @param color The color of the cube.
     * @param center_x The x-coordinate of the cube's center.
     * @param center_y The y-coordinate of the cube's center.
     * @param width The width of the cube.
     */
    Cube(SDL_Renderer *renderer, SDL_Color color, int center_x, int center_y, int width)
        : Shape(renderer, color, center_x, center_y)
    {
        // Initialize the cube's 3D points relative to the center
        int half_width = width / 2;
        pts_relative_to_center_3d.emplace_back(-half_width, -half_width, -half_width); // Bottom left back
        pts_relative_to_center_3d.emplace_back(half_width, -half_width, -half_width);  // Bottom right back
        pts_relative_to_center_3d.emplace_back(half_width, half_width, -half_width);   // Top right back
        pts_relative_to_center_3d.emplace_back(-half_width, half_width, -half_width);  // Top left back
        pts_relative_to_center_3d.emplace_back(-half_width, -half_width, half_width);  // Bottom left front
        pts_relative_to_center_3d.emplace_back(half_width, -half_width, half_width);   // Bottom right front
        pts_relative_to_center_3d.emplace_back(half_width, half_width, half_width);    // Top right front
        pts_relative_to_center_3d.emplace_back(-half_width, half_width, half_width);   // Top left front
    }

    /**
     * @brief Draws the cube on the screen.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    void draw(int offset_x, int offset_y, double scale) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        project();
        convertWorldPointsToScreen(offset_x, offset_y, scale);

        // Draw back face
        drawLine(pts_absolute_2d[0], pts_absolute_2d[1]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[2]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[3]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[0]);

        // Draw front face
        drawLine(pts_absolute_2d[4], pts_absolute_2d[5]);
        drawLine(pts_absolute_2d[5], pts_absolute_2d[6]);
        drawLine(pts_absolute_2d[6], pts_absolute_2d[7]);
        drawLine(pts_absolute_2d[7], pts_absolute_2d[4]);

        // Draw the connections between the front and back faces
        drawLine(pts_absolute_2d[0], pts_absolute_2d[4]);
        drawLine(pts_absolute_2d[1], pts_absolute_2d[5]);
        drawLine(pts_absolute_2d[2], pts_absolute_2d[6]);
        drawLine(pts_absolute_2d[3], pts_absolute_2d[7]);
    }
};

#endif // CUBE_HPP
