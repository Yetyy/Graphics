#include "AffineTransform.h"

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()
{
	double I[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, I);
}

Matrix<> Scaling(double kx, double ky)
{
	double I[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, I);
}

Matrix<> ReflectOX()
{
	return Scaling(-1, 1);
}

Matrix<> ReflectOY()
{
	return Scaling(1, -1);
}

Matrix<> Rotation(double O)
{
	double I[9] = {
		cos(O), -sin(O), 0,
		sin(O), cos(O),  0,
		0,		0,		 1 };
	return Matrix<>(3, 3, I);
}

