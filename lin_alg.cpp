#include "lin_alg.hpp"
#include <stdlib.h>

void matrix_vector_multiply(float **matrix, int vector[], int dim)
{
    int new_vector[dim];

    for (int row = 0; row < dim; row++)
    {
        int new_entry = 0;
        for (int col = 0; col < dim; col++)
        {
            new_entry += matrix[row][col] * vector[col];
        }
        new_vector[row] = new_entry;
    }

    for (int i = 0; i < dim; i++)
    {
        vector[i] = (int)(new_vector[i]);
    }
}

void rotate_pts_x(int p[DIMENSION], int theta)
{
    float **rotation_matrix = (float **)calloc(DIMENSION, sizeof(float *));
    matrix_vector_multiply(rotation_matrix, p, DIMENSION);
}
