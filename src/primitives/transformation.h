#ifndef RTC_PRIMITIVES_TRANSFORMATION_H_
#define RTC_PRIMITIVES_TRANSFORMATION_H_

class Matrix;

Matrix Translation(float x, float y, float z);

Matrix Scaling(float x, float y, float z);

Matrix RotationX(float radians);
Matrix RotationY(float radians);
Matrix RotationZ(float radians);

Matrix Shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

#endif    // RTC_PRIMITIVES_TRANSFORMATION_H_
