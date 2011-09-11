#include <iostream>
#include "mymatrix.h"
#include <cmath>


bool checkDiagonal(const MyMatrix<float, 4>& matrix, float value)
{
	for(int i = 0; i < 16; ++i)
		if(i % 5 == 0 && std::abs(matrix[i] - value) > 0.00001f)
			return false;
	return true;
}

void testIdentity()
{
	MyMatrix<float, 4> matrix;

	std::cerr << "Identity matrix init : ";
	if(checkDiagonal(matrix, 1.0f))
		std::cerr << "OK.\n";
	else
		std::cerr << "Fail!\n";
}

void testDiagonal()
{

	MyMatrix<float,4> matrix(10);
	std::cerr << "Diagonal matrix init : ";

	if(checkDiagonal(matrix, 10.0f))
		std::cerr << "OK.\n";
	else
		std::cerr << "Fail!\n";

}

void testArrayInit()
{
	float array[16];
	for(int i = 0; i < 16; ++i)
	{
		array[i] = i;
	}

	bool success = true;
	MyMatrix<float,4> matrix(array);
	for(int i = 0; i < 16; ++i)
		if(std::abs(matrix[i] - i) > 0.000001f)
			success = false;

	std::cerr << "Matrix from array init : " << (success ? "OK.\n" : "Fail!\n");
}

void testSummationSubstraction()
{
	float array[16];
	for(int i = 0; i < 16; ++i)
		array[i] = i;
	MyMatrix<float, 4> mat1(array);

	for(int i = 0; i < 16; ++i)
		array[i] = 16-i;
	MyMatrix<float, 4> mat2(array);
	MyMatrix<float, 4> result = mat1 + mat2;
	MyMatrix<float, 4> result2 = mat2 - mat1;

	bool success = true;
	for(int i = 0; i < 16; ++i)
		if(std::abs(result[i] - 16) > 0.00001f
				|| std::abs(result2[i] - 16) > 0.00001f
				|| std::abs(mat1[i] - i) > 0.00001f
				|| std::abs(mat2[i] - 16 + i) > 0.00001f)
			success = false;

	std::cerr << "Matrix summation&substraction : " << (success ? "OK.\n" : "Fail!\n");
}

void testMatrixProduct()
{
	float array[16];
	float array2[16];

	for(int i = 0; i < 16; ++i)
	{
		array[i] = i;
		array2[i] = i + 35;
	}

	MyMatrix<float, 4> mat1(array), mat2(array2);
	MyMatrix<float, 4> result = mat1 * mat2;

	float expectedResults[16] = 
	{266, 272, 278, 284,
	 922, 944, 966, 988,
	 1578, 1616, 1654, 1692,
	 2234, 2288, 2342, 2396};

	bool success = true;

	for(int i = 0; i < 16; ++i)
		if(std::abs(result[i] - expectedResults[i]) > 0.000001f)
			success = false;
	result.transpose();

	for(int i = 0; i < 4; ++i)
		for(int j = 4; j < 4; ++j)
		if(std::abs(result[i*4+j] - expectedResults[j*4+i]) > 0.000001f)
			success = false;

	result.transpose();

	for(int i = 0; i < 16; ++i)
		if(std::abs(result[i] - expectedResults[i]) > 0.000001f)
			success = false;
	std::cerr << "Matrix multiplication : " << (success ? "OK.\n" : "Fail!\n");
	if(!success)
	{
		printMatrix(mat1);
		printMatrix(mat2);
		printMatrix(result);
	}
}

int main()
{
	testIdentity();
	testDiagonal();
	testArrayInit();
	testSummationSubstraction();
	testMatrixProduct();

	return 0;
}

