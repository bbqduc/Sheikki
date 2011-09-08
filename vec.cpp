#include <cmath>
#include <cassert>

template<size_t T>
void Vec<T>::set_length(float target)
{
	float length = 0;
	for(int i = 0; i < T; ++i)
		length += (coords[i] * coords[i]);
	
	length = sqrt(length) / target;

	for(int i = 0; i < T; ++i)
		coords[i] /= length;
}

template<size_t T>
Vec<T> operator*(float a, const Vec<T>& vec)
{
	Vec<T> temp(vec);	
	temp *= a;

	return temp;
}

template<size_t T>
Vec<T>& Vec<T>::operator*=(float a)
{
	for(int i = 0; i < T; ++i)
		coords[i] *= a;

	return *this;
}

template<size_t T>
float dot(const Vec<T>& vec1, const Vec<T>& vec2)
{
	float ret = 0;
	for(int i = 0; i < T; ++i)
		ret += (vec1.coords[i] * vec2.coords[i]);

	return ret;
}

template<size_t T>
float& Vec<T>::operator[](size_t index)
{
	assert(index < T);
	return coords[index];
}
