#ifndef VEC_H
#define VEC_H

template<size_t T>
struct Vec
{
	float coords[T];

	void set_length(float);
	operator*=(float a);
};

template<size_t T>
Vec<T> operator*(float a, const Vec<T>& vec);
float dot(const Vec<T>&, const Vec<T>&);

#include "vec3.cpp"
#endif
