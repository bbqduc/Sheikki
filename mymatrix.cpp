#include <iostream>
#include <cmath>

	template<typename T, size_t N>
void MyMatrix<T,N>::transpose()
{
	T temp[N*N];
	for(size_t i = 0; i < N*N; ++i)
		temp[i] = values[i];

	for(size_t i = 0; i < N; ++i)
		for(size_t j = 0; j < N; ++j)
			values[N*i+j] = temp[N*j+i];

}

	template<typename T, size_t N>
MyMatrix<T,N>::MyMatrix(T* array)
{
	for(size_t i = 0; i < N*N; ++i)
		values[i] = array[i];
}

// Initializes diagonal to value and rest to 0
	template<typename T, size_t N>
MyMatrix<T,N>::MyMatrix(T value)
{
	for(size_t i = 0; i < N*N; ++i)
		values[i] = (i % (N+1) == 0) * value;
}

	template<typename T>
MyMatrix<T,3> shrink(const MyMatrix<T,4>& mat)
{
	MyMatrix<T,3> ret;
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; i < 3; ++i)
			ret[3*i+j] = mat[4*i+j];
	return ret;
}

	template<typename T, size_t N>
void printMatrix(const MyMatrix<T,N>& matrix)
{
	std::cerr << "\n";
	for(size_t i = 0; i < N*N; ++i)
		std::cerr << matrix[i] << (( (i+1) % N == 0) ? "\n" : " ");

}

	template<typename T, size_t N>
T& MyMatrix<T,N>::operator[](int index)
{
	return values[index];
}

template<typename T, size_t N>
const T& MyMatrix<T,N>::operator[](int index) const
{
	return values[index];
}

	template<typename T, size_t N>
MyMatrix<T,N>& MyMatrix<T,N>::operator+=(const MyMatrix<T,N>& matrix)
{
	for(size_t i = 0; i < N*N; ++i)
		values[i] += matrix[i];
	return *this;
}

	template<typename T, size_t N>
MyMatrix<T,N> operator+(const MyMatrix<T,N>& b, const MyMatrix<T,N>& a)
{
	MyMatrix<T,N> ret = b;
	ret += a;
	return ret;
}

	template<typename T, size_t N>
MyMatrix<T,N>& MyMatrix<T,N>::operator-=(const MyMatrix<T,N>& matrix)
{
	for(size_t i = 0; i < N*N; ++i)
		values[i] += matrix[i];
	return *this;
}

	template<typename T, size_t N>
MyMatrix<T,N> operator-(const MyMatrix<T,N>& b, const MyMatrix<T,N>& a)
{
	MyMatrix<T,N> ret = b;
	ret -= a;
	return ret;
}

	template<typename T>
MyMatrix<T,4> operator*(const MyMatrix<T,4>& b, const MyMatrix<T,4>& a)
{
	MyMatrix<T,4> m;
	for (int i=0; i<16; i+=4)    
		for (int j=0; j<4; j++)      
			m[i+j] = b[i]*a[j] + b[i+1]*a[j+4] + b[i+2]*a[j+8] + b[i+3]*a[j+12];
	return m;
}

	template<typename T, size_t N>
MyMatrix<T,N>& MyMatrix<T,N>::operator*=(const MyMatrix<T,N>& mat) 
{
	MyMatrix<T,N> m(*this);
	*this = m * mat;

	return *this;
}
