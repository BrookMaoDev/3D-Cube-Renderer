#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

/**
 * @class Point
 * @brief A class to represent a 3D point and perform rotations in 3D space.
 */
class Point
{
private:
    int x;         ///< The x-coordinate of the point.
    int y;         ///< The y-coordinate of the point.
    int z;         ///< The z-coordinate of the point.
    int rotated_x; ///< The x-coordinate after rotation.
    int rotated_y; ///< The y-coordinate after rotation.
    int rotated_z; ///< The z-coordinate after rotation.

public:
    /**
     * @brief Constructor to initialize the point coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param z The z-coordinate.
     */
    Point(int x, int y, int z) : x(x), y(y), z(z), rotated_x(x), rotated_y(y), rotated_z(z) {}

    /**
     * @brief Gets the x-coordinate after rotation.
     * @return The rotated x-coordinate.
     */
    int getRotatedX() const
    {
        return rotated_x;
    }

    /**
     * @brief Gets the y-coordinate after rotation.
     * @return The rotated y-coordinate.
     */
    int getRotatedY() const
    {
        return rotated_y;
    }

    /**
     * @brief Gets the z-coordinate after rotation.
     * @return The rotated z-coordinate.
     */
    int getRotatedZ() const
    {
        return rotated_z;
    }

    /**
     * @brief Rotates the point around the x, y, and z axes by a given angle.
     * @param theta The angle of rotation in radians.
     */
    void rotate(double theta)
    {
        // Temporary variables for rotation
        int temp_x, temp_y, temp_z;

        // Rotate the point around the x-axis
        temp_y = static_cast<int>(y * cos(theta) - z * sin(theta));
        temp_z = static_cast<int>(y * sin(theta) + z * cos(theta));
        rotated_x = x;
        rotated_y = temp_y;
        rotated_z = temp_z;

        // Rotate the point around the y-axis
        temp_x = static_cast<int>(rotated_x * cos(theta) + rotated_z * sin(theta));
        temp_z = static_cast<int>(-rotated_x * sin(theta) + rotated_z * cos(theta));
        rotated_x = temp_x;
        rotated_z = temp_z;

        // Rotate the point around the z-axis
        temp_x = static_cast<int>(rotated_x * cos(theta) - rotated_y * sin(theta));
        temp_y = static_cast<int>(rotated_x * sin(theta) + rotated_y * cos(theta));
        rotated_x = temp_x;
        rotated_y = temp_y;
    }
};

#endif // POINT_HPP
