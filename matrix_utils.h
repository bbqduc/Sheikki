#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include "mymatrix.h"

MyMatrix<float,4> projectionMatrix(float fov, float aspect, float znear, float zfar);
MyMatrix<float,4> rotationMatrix(float angle, float x, float y, float z);
MyMatrix<float,4> translationMatrix(float x, float y, float z);

#endif
