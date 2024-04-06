#ifndef CUBE_H
#define CUBE_H

#include "SDL.h"

class Cube
{
private:
    static const int DIMENSION = 3;        // Dimension the cube is in
    static const int SCREEN_DIMENSION = 2; // Dimension of the screen

    int center_x; // X coordinate of the centroid of the cube
    int center_y; // Y coordinate of the centroid of the cube

    int width;                                 // Distance between any 2 vertices, which can be modified by the user
    static const int MIN_WIDTH = 10;           // The smallest that width can be made
    static constexpr double ZOOM_AMOUNT = 1.1; // The ratio to zoom in or out by when prompted to by the user

    double total_rotation = 0; // Tracks how much the cube has been rotated in total

    static const int NUM_PTS = 8;                // Number of vertices
    int reference_pts_in_3d[NUM_PTS][DIMENSION]; // Position of vertices before transformations relative to (0, 0, 0)
    int pts_in_3d[NUM_PTS][DIMENSION];           // Position of vertices after transformations relative to (0, 0, 0)
    int pts_in_2d[NUM_PTS][SCREEN_DIMENSION];    // Position of vertices projected onto the 2D screen

    // Indices for the positions of vertices
    static const int X_INDEX = 0;
    static const int Y_INDEX = 1;
    static const int Z_INDEX = 2;

    /**
     * @brief Draws an undirected line
     * @param renderer Renderer the line is rendered in
     * @param p1 A point in 2D
     * @param p2 A point in 2D
     */
    void draw_line(SDL_Renderer *renderer, int p1[SCREEN_DIMENSION], int p2[SCREEN_DIMENSION]);

    /**
     * @brief Updates pts_in_2d according to pts_in_3d
     */
    void project();

    /**
     * @brief Populates reference_pts_in_3d
     * @param width Width of cube
     */
    void set_reference_pts(int width);

public:
    /**
     * @brief Constructor
     * @param center_x X coordinate of the centroid of the cube
     * @param center_y Y coordinate of the centroid of the cube
     * @param width Width of cube
     */
    Cube(int center_x, int center_y, int width);

    /**
     * @brief Draws the cube with the current information onto the screen
     * @param renderer Renderer the cube is rendered in
     */
    void draw_cube(SDL_Renderer *renderer);

    /**
     * @brief Rotates each point in the cube
     * @param theta Angle in radians to rotate by
     */
    void rotate_cube(double theta);

    /**
     * @brief Increases the cube’s width by a factor of ZOOM_AMOUNT
     */
    void zoom_in();

    /**
     * @brief Decreases the cube’s width by a factor of ZOOM_AMOUNT
     */
    void zoom_out();

    /**
     * @brief Updates the center_y field variable
     * @param y Amount to shift up by
     */
    void shift_up(int y);

    /**
     * @brief Updates the center_x field variable
     * @param y Amount to shift left by
     */
    void shift_left(int x);
};

#endif
