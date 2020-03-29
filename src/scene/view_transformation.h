#ifndef RTC_SCENE_VIEW_TRANSFORMATION_H
#define RTC_SCENE_VIEW_TRANSFORMATION_H

class Matrix;
class Tuple;

Matrix ViewTransformation(Tuple from, Tuple to, Tuple up);

#endif    // RTC_SCENE_VIEW_TRANSFORMATION_H
