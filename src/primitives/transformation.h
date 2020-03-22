#ifndef RTC_PRIMITIVES_TRANSFORMATION_H_
#define RTC_PRIMITIVES_TRANSFORMATION_H_

class Matrix;

Matrix Translation(float x, float y, float z);
Matrix Scaling(float x, float y, float z);

Matrix RotationX(float radians);
Matrix RotationY(float radians);
Matrix RotationZ(float radians);

#endif    // RTC_PRIMITIVES_TRANSFORMATION_H_
