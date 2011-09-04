#include "mymatrix.h"
#include <iostream>
#include <cmath>

MyMatrix::MyMatrix(float* array)
{
	for(int i = 0; i < 16; ++i)
		values[i] = array[i];
}

// Initializes diagonal to value and rest to 0
MyMatrix::MyMatrix(float value)
{
	for(int i = 0; i < 16; ++i)
		values[i] = (i % 5 == 0) * value;
}

void printMatrix(const MyMatrix& matrix)
{
	std::cerr << "\n";
	for(int i = 0; i < 16; ++i)
		std::cerr << matrix[i] << (( (i+1) % 4 == 0) ? "\n" : " ");

}

float& MyMatrix::operator[](int index)
{
	return values[index];
}

const float& MyMatrix::operator[](int index) const
{
	return values[index];
}

MyMatrix rotationMatrix(float angle, float x, float y, float z)
{
	float c = cos(angle);
	float d = 1 - c;

	float s = sin(angle);

	float array[16] = 
	{c + x*x*d, x*y*d- z*s, x*z*d + y*s, 0,
	y*x*d + z*s, c + y*y*d, y*z*d - x*s, 0,
	z*x*d - y*s, z*y*d + x*s, c + z*z*d, 0,
	0, 0, 0, 1};

	return MyMatrix(array);
}

MyMatrix translationMatrix(float x, float y, float z)
{
	MyMatrix matrix;
	matrix[3] = x;
	matrix[7] = y;
	matrix[11] = z;

	return matrix;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& matrix)
{
	for(int i = 0; i < 16; ++i)
		values[i] += matrix[i];
	return *this;
}

MyMatrix operator+(const MyMatrix& b, const MyMatrix& a)
{
	MyMatrix ret = b;
	ret += a;
	return ret;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& matrix)
{
	for(int i = 0; i < 16; ++i)
		values[i] += matrix[i];
	return *this;
}

MyMatrix operator-(const MyMatrix& b, const MyMatrix& a)
{
	MyMatrix ret = b;
	ret -= a;
	return ret;
}

MyMatrix operator*(const MyMatrix& b, const MyMatrix& a)
{
	MyMatrix m;
	for (int i=0; i<16; i+=4)    
		for (int j=0; j<4; j++)      
			m[i+j] = b[i]*a[j] + b[i+1]*a[j+4] + b[i+2]*a[j+8] + b[i+3]*a[j+12];
	return m;
}

MyMatrix projectionMatrix(float fov, float aspect, float znear, float zfar)
{
	MyMatrix m(0.0f);
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
