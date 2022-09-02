#include "pch.h"
#include "Curve.h"
//
//Curve::Curve()
//{
//
//}
//
//void Curve::checkMinMax(float x)
//{
//	if (x < minX) minX = x;
//	if (x > maxX) maxX = x;
//}
//
//void Curve::addPoint(float2 pos, float angle, float radius)
//{
//	checkMinMax(pos.x);
//	float2 direction = {cos(angle), sin(angle)};
//	points.push_back({ pos, direction, radius});
//}
//
//void Curve::addPoint(float2 pos, float2 direction, float radius)
//{
//	checkMinMax(pos.x);
//	points.push_back({pos, direction, radius});
//}
//
//void Curve::addPoint(float2 pos, float dy, float radius)
//{
//	checkMinMax(pos.x);
//	float2 direction = mymath::normalize(float2({ 1, dy }));
//	points.push_back({ pos, direction, radius});
//}
//
//float Curve::getValue(float x)
//{
//	if(points.size() == 0)
//		return 0;
//
//	if (x < minX || x > maxX)
//		return 0;
//
//	float dLeft = -INFINITY;
//	int leftId;
//
//	float dRight = INFINITY;
//	int rightId;
//
//	for (int i = 0; i < points.size(); i++)
//	{
//		float d = points[i].position.x - x;
//		if (d < 0 && d > dLeft)
//		{
//			dLeft = d;
//			leftId = i;
//		}
//		if (d > 0 && d < dRight)
//		{
//			d = dRight;
//			rightId = i;
//		}
//	}
//
//
//
//	
//}