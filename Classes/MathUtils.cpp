#include "../Classes/MathUtils.h"

float radians_to_degrees(float radians)
{
	return radians * (180 / M_PI);
}

bool belongs(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 point, float fuzziness)
{
	cocos2d::Vec2 left;
	cocos2d::Vec2 right;

	// Normalize start/end to left right to make the offset calc simpler.
	if (A.x <= B.x)
	{
		left = A;
		right = B;
	}
	else
	{
		left = B;
		right = A;
	}

	// If point is out of bounds, no need to do further checks.                  
	if (point.x + fuzziness < left.x || right.x < point.x - fuzziness)
		return false;
	else if (point.y + fuzziness < std::min(left.y, right.y) || std::max(left.y, right.y) < point.y - fuzziness)
		return false;

	double delta_x = right.x - left.x;
	double delta_y = right.y - left.y;

	// If the line is straight, the earlier boundary check is enough to determine that the point is on the line.
	// Also prevents division by zero exceptions.
	if (delta_x == 0 || delta_y == 0)
		return true;

	double slope = delta_y / delta_x;
	double offset = left.y - left.x * slope;
	double calculated_Y = point.x * slope + offset;

	// Check calculated y matches the points y coord with some easing.
	bool contains = point.y - fuzziness <= calculated_Y && calculated_Y <= point.y + fuzziness;

	return contains;


	/*double vec_product = (point.x - A.x) * (B.y - A.y) - (point.y - A.y) * (B.x - A.x);

	return ((vec_product == 0) &&
		   ((A.x <= point.x && point.x <= B.x) ||
		   (B.x <= point.x && point.x <= A.x)) &&
		   ((A.y <= point.y && point.y <= B.y) ||
		   (B.y <= point.y && point.y <= A.y)));

	return false;*/
}
