#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <stdint.h>
#include <cstdlib>

template<typename T, size_t N>
class MyMatrix
{
	T values[N*N];
	public:
	MyMatrix<T,N>(T value = 1.0f);
	MyMatrix<T,N>(T*);

	T& operator[](int);
	const T& operator[](int) const;
	const float& getX() const {return values[3];}
	const float& getY() const {return values[3+N];}
	const float& getZ() const {return values[3+2*N];}
	MyMatrix<T,N>& operator+=(const MyMatrix<T,N>&);
	MyMatrix<T,N>& operator-=(const MyMatrix<T,N>&);
	MyMatrix<T,N>& operator*=(const MyMatrix<T,N>&);

	void transpose();
};

template<typename T, size_t N>
MyMatrix<T,N> operator-(const MyMatrix<T,N>&, const MyMatrix<T,N>&);
template<typename T, size_t N>
MyMatrix<T,N> operator+(const MyMatrix<T,N>&, const MyMatrix<T,N>&);
template<typename T>
MyMatrix<T,4> operator*(const MyMatrix<T,4>&, const MyMatrix<T,4>&);
template<typename T, size_t N>
MyMatrix<T,N> operator*(const MyMatrix<T,N>& a, const MyMatrix<T,N>& b);
template<typename T, size_t N>
void printMatrix(const MyMatrix<T,N>&);

#include "mymatrix.cpp"
#endif
