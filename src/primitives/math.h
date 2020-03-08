#ifndef RTC_PRIMITIVES_MATH_H_
#define RTC_PRIMITIVES_MATH_H_

#include <stdlib.h>

const float EPSION = 0.00001;

inline bool epsilon_eq(float a, float b) { return abs(a - b) < EPSION; };

#endif    // RTC_PRIMITIVES_MATH_H_
