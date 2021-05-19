#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "cocos2d.h"

float radians_to_degrees(float radians);

bool belongs(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 point, float fuzziness = 1);

#endif // !MATH_UTILS_H
