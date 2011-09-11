#include <cmath>
#include <cassert>

template<typename T, size_t N>
void Vec<T,N>::set_length(T target)
{
	float length = this->length() / target;

	for(size_t i = 0; i < N; ++i)
		coords[i] /= length;
}

template<typename T, size_t N>
float Vec<T,N>::length()
{
	float length = 0;
	for(size_t i = 0; i < N; ++i)
		length += (coords[i] * coords[i]);
	
	return sqrt(length);
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
	for(size_t i = 0; i < N; ++i)
		coords[i] *= a;

	return *this;
}

template<typename T, size_t N>
T dot(const Vec<T,N>& vec1, const Vec<T,N>& vec2)
{
	T ret = 0;
	for(size_t i = 0; i < N; ++i)
		ret += (vec1.coords[i] * vec2.coords[i]);

	return ret;
}

template<typename T, size_t N>
T& Vec<T,N>::operator[](size_t index)
{
	assert(index < N);
	return coords[index];
}

template<typename T, size_t N>
const T& Vec<T,N>::operator[](size_t index) const
{
	assert(index < N);
	return coords[index];
}

template<typename T, size_t N>
Vec<T,N>& Vec<T,N>::operator-=(const Vec<T, N>& vec)
{
	for(size_t i = 0; i < N; ++i)
	{
		coords[i] -= vec[i];
	}
	return *this;
}

template<typename T, size_t N>
Vec<T,N>& Vec<T,N>::operator+=(const Vec<T, N>& vec)
{
	for(size_t i = 0; i < N; ++i)
	{
		coords[i] += vec[i];
	}
	return *this;
}

template<typename T>
Vec<T,3> cross(const Vec<T,3>& vec1, const Vec<T,3>& vec2)
{
	Vec<T,3> ret;

	ret[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	ret[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	ret[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

	return ret;
}

template<typename T, size_t N>
Vec<T,N> operator+(const Vec<T,N>&  vec1, const Vec<T,N>& vec2)
{
	Vec<T,N> ret(vec1);
	ret += vec2;

	return ret;
}

template<typename T, size_t N>
Vec<T,N> operator-(const Vec<T,N>&  vec1, const Vec<T,N>& vec2)
{
	Vec<T,N> ret(vec1);
	ret -= vec2;

	return ret;
}
