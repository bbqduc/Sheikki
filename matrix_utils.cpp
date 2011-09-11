#include "matrix_utils.h"

MyMatrix<float,4> rotationMatrix(float angle, float x, float y, float z)
{
	float c = cos(angle);
	float d = 1 - c;

	float s = sin(angle);

	float array[16] = 
	{c + x*x*d, x*y*d- z*s, x*z*d + y*s, 0,
		y*x*d + z*s, c + y*y*d, y*z*d - x*s, 0,
		z*x*d - y*s, z*y*d + x*s, c + z*z*d, 0,
		0, 0, 0, 1};

	return MyMatrix<float,4>(array);
}

MyMatrix<float, 4> translationMatrix(float x, float y, float z)
{
	MyMatrix<float, 4> matrix;
	matrix[3] = x;
	matrix[7] = y;
	matrix[11] = z;

	return matrix;
}

MyMatrix<float,4> projectionMatrix(float fov, float aspect, float znear, float zfar)
{
	MyMatrix<float,4> m(0.0f);
	float xymax = znear * tan(fov);
	float ymin = -xymax;
	float xmin = -xymax;

	float width = xymax - xmin;
	float height = xymax - ymin;

	float depth = zfar - znear;
	float q = -(zfar + znear) / depth;
	float qn = -2 * (zfar * znear) / depth;

	float w = 2 * znear / width;
	w = w / aspect;
	float h = 2 * znear / height;

	m[0]  = w;

	m[5]  = h;

	m[10] = q;
	m[11] = qn;

	m[14] = -1;

	return m;
}
