#ifndef VEC_H
#define VEC_H

template<size_t T>
struct Vec
{
	float coords[T];

	void set_length(float);
	Vec& operator*=(float a);
	float& operator[](size_t);
};

template<size_t T>
Vec<T> operator*(float a, const Vec<T>& vec);
template<size_t T>
float dot(const Vec<T>&, const Vec<T>&);

#include "vec.cpp"
#endif
