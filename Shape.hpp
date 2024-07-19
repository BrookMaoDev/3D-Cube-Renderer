#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "SDL.h"
#include "Point.hpp"
#include <vector>

/**
 * @class Shape
 * @brief A base class for representing and manipulating shapes that can be rendered using SDL.
 */
class Shape
{
protected:
    SDL_Renderer *renderer;                       ///< The SDL renderer used for drawing the shape.
    SDL_Color color;                              ///< The color of the shape.
    int center_x;                                 ///< The x-coordinate of the shape's center.
    int center_y;                                 ///< The y-coordinate of the shape's center.
    std::vector<Point> pts_relative_to_center_3d; ///< Points relative to the center in 3D space.
    std::vector<SDL_Point> pts_absolute_2d;       ///< Points in absolute 2D space after projection.
    double theta = 0.01;                          ///< Incremental angle of rotation.
    double total_rotation = 0;                    ///< Total accumulated rotation.
    static constexpr double deltaTheta = 0.001;   ///< Incremental change in rotation speed.
    static constexpr double minTheta = 0.005;     ///< Minimum rotation speed.
    static constexpr double maxTheta = 0.1;       ///< Maximum rotation speed.

    /**
     * @brief Projects the 3D points relative to the center to 2D absolute world coordinates.
     */
    void project()
    {
        pts_absolute_2d.clear();
        for (Point &pt : pts_relative_to_center_3d)
        {
            int x = center_x + pt.getRotatedX();
            int y = center_y + pt.getRotatedY();
            pts_absolute_2d.push_back(SDL_Point{x, y});
        }
    }

    /**
     * @brief Draws a line between two SDL points.
     * @param pt1 The first point.
     * @param pt2 The second point.
     */
    void drawLine(const SDL_Point &pt1, const SDL_Point &pt2)
    {
        SDL_RenderDrawLine(renderer, pt1.x, pt1.y, pt2.x, pt2.y);
    }

    /**
     * @brief Converts a point from world coordinates to screen coordinates.
     * @param pt The point in world coordinates.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     * @return The point in screen coordinates.
     */
    SDL_Point worldToScreen(const SDL_Point &pt, int offset_x, int offset_y, double scale)
    {
        return SDL_Point{static_cast<int>((pt.x + offset_x) * scale), static_cast<int>((pt.y + offset_y) * scale)};
    }

    /**
     * @brief Converts all world points to screen points.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    void convertWorldPointsToScreen(int offset_x, int offset_y, double scale)
    {
        for (SDL_Point &pt : pts_absolute_2d)
        {
            pt = worldToScreen(pt, offset_x, offset_y, scale);
        }
    }

public:
    /**
     * @brief Constructor to initialize the shape with a renderer, color, and center position.
     * @param renderer The SDL renderer.
     * @param color The color of the shape.
     * @param center_x The x-coordinate of the shape's center.
     * @param center_y The y-coordinate of the shape's center.
     */
    Shape(SDL_Renderer *renderer, SDL_Color color, int center_x, int center_y)
        : renderer(renderer), color(color), center_x(center_x), center_y(center_y) {}

    /**
     * @brief Sets the SDL renderer.
     * @param renderer The SDL renderer.
     */
    void setRenderer(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
    }

    /**
     * @brief Sets the color of the shape.
     * @param color The new color.
     */
    void setColor(SDL_Color color)
    {
        this->color = color;
    }

    /**
     * @brief Rotates the shape by the incremental angle theta.
     */
    void rotate()
    {
        total_rotation += theta;
        for (Point &pt : pts_relative_to_center_3d)
        {
            pt.rotate(total_rotation);
        }
    }

    /**
     * @brief Increases the speed of rotation.
     */
    void speedUp()
    {
        double newTheta = theta + Shape::deltaTheta;
        theta = (newTheta <= maxTheta) ? newTheta : maxTheta;
    }

    /**
     * @brief Decreases the speed of rotation.
     */
    void slowDown()
    {
        double newTheta = theta - Shape::deltaTheta;
        theta = (newTheta >= minTheta) ? newTheta : minTheta;
    }

    /**
     * @brief Pure virtual method to draw the shape.
     * @param offset_x The x offset for drawing.
     * @param offset_y The y offset for drawing.
     * @param scale The scale for drawing.
     */
    virtual void draw(int offset_x, int offset_y, double scale) = 0;
};

#endif // SHAPE_HPP
