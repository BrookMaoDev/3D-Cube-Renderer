#ifndef CUBE_H
#define CUBE_H

#include "SDL.h"

class Cube
{
private:
    static const int NUM_PTS = 8;
    static const int DIMENSION = 3;
    static const int SCREEN_DIMENSION = 2;
    static const int X_INDEX = 0;
    static const int Y_INDEX = 1;
    static const int Z_INDEX = 2;
    const double THETA = 0.01;
    double total_rotation = 0;
    int CENTER_X;
    int CENTER_Y;
    int orig_pts_in_3d[NUM_PTS][DIMENSION];
    int pts_in_3d[NUM_PTS][DIMENSION];
    int pts_in_2d[NUM_PTS][SCREEN_DIMENSION];

    void draw_line(SDL_Renderer *renderer, int p1[SCREEN_DIMENSION], int p2[SCREEN_DIMENSION]);
    void project();

public:
    Cube(int CENTER_X, int CENTER_Y, int width);
    ~Cube();

    void draw_cube(SDL_Renderer *renderer);
    void rotate_cube();
};

#endif
