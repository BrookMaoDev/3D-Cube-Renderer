#ifndef CUBE_H
#define CUBE_H

#include "SDL.h"
#include <cmath>

class Cube
{
private:
    static const int NUM_PTS = 8;
    static const int DIMENSION = 3;
    static const int SCREEN_DIMENSION = 2;
    static const int X_INDEX = 0;
    static const int Y_INDEX = 1;
    static const int Z_INDEX = 2;

    const int THETA = 1;

    int pts_in_3d[NUM_PTS][DIMENSION];
    int pts_in_2d[NUM_PTS][SCREEN_DIMENSION];

    void draw_line(SDL_Renderer *renderer, int p1[SCREEN_DIMENSION], int p2[SCREEN_DIMENSION]);

public:
    Cube(int pts_in_3d[NUM_PTS][DIMENSION]);
    ~Cube();

    void draw_cube(SDL_Renderer *renderer);
    void rotate_cube();
};

#endif
