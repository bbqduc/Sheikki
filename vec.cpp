#include <cmath>
#include <cassert>

template<typename T, size_t N>
void Vec<T,N>::set_length(T target)
{
	T length = 0;
	for(int i = 0; i < N; ++i)
		length += (coords[i] * coords[i]);
	
	length = sqrt(length) / target;

	for(int i = 0; i < N; ++i)
		coords[i] /= length;
}

template<typename T, size_t N>
Vec<T,N> operator*(T a, const Vec<T,N>& vec)
{
	Vec<T,N> temp(vec);	
	temp *= a;

	return temp;
}

template<typename T, size_t N>
Vec<T,N>& Vec<T,N>::operator*=(T a)
{
	for(int i = 0; i < N; ++i)
		coords[i] *= a;

	return *this;
}

template<typename T, size_t N>
T dot(const Vec<T,N>& vec1, const Vec<T,N>& vec2)
{
	T ret = 0;
	for(int i = 0; i < N; ++i)
		ret += (vec1.coords[i] * vec2.coords[i]);

	return ret;
}

template<typename T, size_t N>
T& Vec<T,N>::operator[](size_t index)
{
	assert(index < N);
	return coords[index];
}
