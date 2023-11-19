#pragma once
#include "Matrix.h"

# define M_PI 3.14159265358979323846

Matrix<> Translation(double x, double y);

Matrix<> Identity();

Matrix<> Scaling(double kx, double ky);

Matrix<> ReflectOX();

Matrix<> ReflectOY();

Matrix<> Rotation(double O);
