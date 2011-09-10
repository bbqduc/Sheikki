#ifndef MYMATRIX_H
#define MYMATRIX_H


class MyMatrix
{
	float values[16];
	public:
	MyMatrix(float value = 1.0f);
	MyMatrix(float*);
	float& operator[](int);
	const float& operator[](int) const;
	MyMatrix& operator+=(const MyMatrix&);
	MyMatrix& operator-=(const MyMatrix&);
	MyMatrix& operator*=(const MyMatrix&);
};

MyMatrix operator-(const MyMatrix&, const MyMatrix&);
MyMatrix operator+(const MyMatrix&, const MyMatrix&);
MyMatrix operator*(const MyMatrix&, const MyMatrix&);
MyMatrix rotationMatrix(float angle, float x, float y, float z);
MyMatrix translationMatrix(float x, float y, float z);
MyMatrix operator*(const MyMatrix& a, const MyMatrix& b);
MyMatrix projectionMatrix(float fov, float aspect, float znear, float zfar);
void printMatrix(const MyMatrix&);
#endif
