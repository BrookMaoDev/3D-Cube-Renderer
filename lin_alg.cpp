#include "lin_alg.hpp"
#include <stdlib.h>
#include <cmath>

void matrix_vector_multiply(std::vector<std::vector<double>> &matrix, int vector[], int dim)
{
    // Array to store the entries for the resultant vector
    int new_vector[dim];

    // Matrix vector multiplication algorithm
    for (int row = 0; row < dim; row++)
    {
        double new_entry = 0;
        for (int col = 0; col < dim; col++)
        {
            new_entry += matrix[row][col] * vector[col];
        }
        new_vector[row] = new_entry;
    }

    // Copy the resultant entries into the passed in vector array
    for (int i = 0; i < dim; i++)
    {
        vector[i] = new_vector[i];
    }
}

void rotate_pt_x(int p[DIMENSION], double theta)
{
    std::vector<std::vector<double>> rotation_matrix = {{1, 0, 0},
                                                        {0, cos(theta), -sin(theta)},
                                                        {0, sin(theta), cos(theta)}};
    matrix_vector_multiply(rotation_matrix, p, DIMENSION);
}

void rotate_pt_y(int p[DIMENSION], double theta)
{
    std::vector<std::vector<double>> rotation_matrix = {{cos(theta), 0, sin(theta)},
                                                        {0, 1, 0},
                                                        {-sin(theta), 0, cos(theta)}};
    matrix_vector_multiply(rotation_matrix, p, DIMENSION);
}

void rotate_pt_z(int p[DIMENSION], double theta)
{
    std::vector<std::vector<double>> rotation_matrix = {{cos(theta), -sin(theta), 0},
                                                        {sin(theta), cos(theta), 0},
                                                        {0, 0, 1}};
    matrix_vector_multiply(rotation_matrix, p, DIMENSION);
}
