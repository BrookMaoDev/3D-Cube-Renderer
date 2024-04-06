#ifndef LIN_ALG_H
#define LIN_ALG_H

#include <vector>

const int DIMENSION = 3; // Dimension of R3

/**
 * @brief Rotates a point in r3 along the x axis
 * @param p A point in R3
 * @param theta Angle in radians to rotate by
 */
void rotate_pt_x(int p[DIMENSION], double theta);

/**
 * @brief Rotates a point in r3 along the y axis
 * @param p A point in R3
 * @param theta Angle in radians to rotate by
 */
void rotate_pt_y(int p[DIMENSION], double theta);

/**
 * @brief Rotates a point in r3 along the z axis
 * @param p A point in R3
 * @param theta Angle in radians to rotate by
 */
void rotate_pt_z(int p[DIMENSION], double theta);

/**
 * @brief Performs matrix vector multiplication, replacing each entry in vector
 * @param matrix A square matrix
 * @param vector An array representing a vector in Rn
 * @param dim Length of vector and dimension of matrix
 */
void matrix_vector_multiply(std::vector<std::vector<double>> &matrix, int vector[], int dim);

#endif
