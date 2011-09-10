#ifndef VEC_H
#define VEC_H

template<typename T, size_t N>
struct Vec
{
	T coords[N];

	void set_length(T);
	Vec& operator*=(T a);
	T& operator[](size_t);
};

template<typename T, size_t N>
Vec<T,N> operator*(T a, const Vec<T,N>& vec);
template<typename T, size_t N>
T dot(const Vec<T,N>&, const Vec<T,N>&);

#include "vec.cpp"
#endif
