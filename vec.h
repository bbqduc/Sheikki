#ifndef VEC_H
#define VEC_H

template<typename T, size_t N>
class Vec
{
	T coords[N];

	public:
	float length();
	void set_length(T);
	Vec& operator*=(T a);
	Vec& operator-=(const Vec<T, N>&);
	Vec& operator+=(const Vec<T, N>&);
	T& operator[](size_t);
	const T& operator[](size_t) const;
};

template<typename T, size_t N>
Vec<T,N> operator*(T a, const Vec<T,N>& vec);
template<typename T, size_t N>
Vec<T,N> operator-(const Vec<T,N>&  vec1, const Vec<T,N>& vec2);
template<typename T, size_t N>
Vec<T,N> operator+(const Vec<T,N>&  vec1, const Vec<T,N>& vec2);
template<typename T, size_t N>
T dot(const Vec<T,N>&, const Vec<T,N>&);
template<typename T>
Vec<T,3> cross(const Vec<T,3>&, const Vec<T,3>&);

#include "vec.cpp"
#endif
