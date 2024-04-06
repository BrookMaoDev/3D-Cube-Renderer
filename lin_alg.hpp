#ifndef LIN_ALG_H
#define LIN_ALG_H

#include <vector>

const int DIMENSION = 3;

void rotate_pt_x(int p[DIMENSION], double theta);
void rotate_pt_y(int p[DIMENSION], double theta);
void rotate_pt_z(int p[DIMENSION], double theta);
void matrix_vector_multiply(std::vector<std::vector<double>> &matrix, int vector[], int dim);

#endif
