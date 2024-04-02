#include "cube.hpp"
#include "lin_alg.hpp"

// for debugging
#include <iostream>

Cube::Cube(int CENTER_X, int CENTER_Y, int width)
{
    this->CENTER_X = CENTER_X;
    this->CENTER_Y = CENTER_Y;

    int pts[NUM_PTS][DIMENSION] = {
        // Front face vertices
        {-width / 2, -width / 2, 0}, // Bottom left front
        {+width / 2, -width / 2, 0}, // Bottom right front
        {+width / 2, +width / 2, 0}, // Top right front
        {-width / 2, +width / 2, 0}, // Top left front
        // Back face vertices
        {-width / 2, -width / 2, width}, // Bottom left back
        {+width / 2, -width / 2, width}, // Bottom right back
        {+width / 2, +width / 2, width}, // Top right back
        {-width / 2, +width / 2, width}  // Top left back
    };

    for (int pt = 0; pt < NUM_PTS; pt++)
    {
        for (int dim = 0; dim < DIMENSION; dim++)
        {
            this->pts_in_3d[pt][dim] = pts[pt][dim];
        }
    }

    for (int pt = 0; pt < NUM_PTS; pt++)
    {
        for (int dim = 0; dim < SCREEN_DIMENSION; dim++)
        {
            this->pts_in_2d[pt][dim] = pts_in_3d[pt][dim];
        }
    }
}

Cube::~Cube()
{
}

void Cube::draw_line(SDL_Renderer *renderer, int p1[SCREEN_DIMENSION], int p2[SCREEN_DIMENSION])
{
    SDL_RenderDrawLine(renderer, p1[X_INDEX], p1[Y_INDEX], p2[X_INDEX], p2[Y_INDEX]);
}

void Cube::draw_cube(SDL_Renderer *renderer)
{
    printf("[%d, %d, %d]\n", pts_in_3d[0][X_INDEX], pts_in_3d[0][Y_INDEX], pts_in_3d[0][Z_INDEX]);

    // Front face
    draw_line(renderer, pts_in_2d[0], pts_in_2d[1]); // Bottom left to bottom right
    draw_line(renderer, pts_in_2d[1], pts_in_2d[2]); // Bottom right to top right
    draw_line(renderer, pts_in_2d[2], pts_in_2d[3]); // Top right to top left
    draw_line(renderer, pts_in_2d[3], pts_in_2d[0]); // Top left to bottom left

    // Back face
    draw_line(renderer, pts_in_2d[4], pts_in_2d[5]); // Bottom left to bottom right
    draw_line(renderer, pts_in_2d[5], pts_in_2d[6]); // Bottom right to top right
    draw_line(renderer, pts_in_2d[6], pts_in_2d[7]); // Top right to top left
    draw_line(renderer, pts_in_2d[7], pts_in_2d[4]); // Top left to bottom left

    // Connect front and back faces
    draw_line(renderer, pts_in_2d[0], pts_in_2d[4]); // Bottom left front to bottom left back
    draw_line(renderer, pts_in_2d[1], pts_in_2d[5]); // Bottom right front to bottom right back
    draw_line(renderer, pts_in_2d[2], pts_in_2d[6]); // Top right front to top right back
    draw_line(renderer, pts_in_2d[3], pts_in_2d[7]); // Top left front to top left back

    SDL_RenderPresent(renderer);
}

void Cube::rotate_cube()
{
    for (int i = 0; i < NUM_PTS; i++)
    {
        rotate_pt_x(pts_in_3d[i], THETA);
    }

    for (int i = 0; i < NUM_PTS; i++)
    {
        rotate_pt_y(pts_in_3d[i], THETA);
    }

    project();
}

void Cube::project()
{
    for (int i = 0; i < NUM_PTS; i++)
    {
        pts_in_2d[i][X_INDEX] = pts_in_3d[i][X_INDEX] + CENTER_X;
        pts_in_2d[i][Y_INDEX] = pts_in_3d[i][Y_INDEX] + CENTER_Y;
    }
}
