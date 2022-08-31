#pragma once
#include <iostream>
#define PI 3.14159265359

struct long2
{
	long x;
	long y;
};

struct float2
{
	float x;
	float y;
};

struct float3
{
	float x, y, z;

	float3 operator/(float val)
	{
		return float3{ x / val, y / val, z / val };
	}

	float3 operator*(float val)
	{
		return float3{ x * val, y * val, z * val };
	}

	void operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
	}

	void operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
	}

	void operator+=(float3 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	void operator-=(float3 vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}

	float3 operator-(float3 vec) const
	{
		return {x - vec.x, y - vec.y, z - vec.z};
	}

	float3 operator+(float3 vec) const
	{
		return { x + vec.x, y + vec.y, z + vec.z };
	}

	bool operator!=(float3 const vec) const
	{
		if (x != vec.x || y != vec.y || z != vec.z)
			return true;
		else
			return false;
	}
};

struct double3
{
	double x, y, z;

	double3 operator/(double val)
	{
		return double3{ x / val, y / val, z / val };
	}

	double3 operator*(double val)
	{
		return double3{ x * val, y * val, z * val };
	}

	void operator/=(double val)
	{
		x /= val;
		y /= val;
		z /= val;
	}

	void operator*=(double val)
	{
		x *= val;
		y *= val;
		z *= val;
	}

	void operator+=(double3 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	void operator-=(double3 vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}
};

struct float4
{
	float x;
	float y;
	float z;
	float w;
};

class mymath
{
public:
	static float getLength(float3 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	static double getLength(double3 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	static float3 normalize(float3 vec)
	{
		return vec / getLength(vec);
	}

	static double3 normalize(double3 vec)
	{
		return vec / getLength(vec);
	}

	static void setLength(float3* vec, float length)
	{
		*vec = normalize(*vec) * length;
	}

	static void setLength(double3* vec, double length)
	{
		*vec = normalize(*vec) * length;
	}

	static float interpolate(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	static float getAngle(float originAxisCoord, float noRotationAxisCoord) { // (координата по оси, относительно которой расчитывается угол; координата по оси, относительно которой НЕ происходит вращение)
		if (originAxisCoord == 0 && noRotationAxisCoord > 0) return PI / 2;
		if (originAxisCoord == 0 && noRotationAxisCoord < 0) return 3 * PI / 2;

		float angle = std::atan(noRotationAxisCoord / originAxisCoord);

		if (originAxisCoord < 0) angle += PI;
		if (originAxisCoord > 0 && noRotationAxisCoord < 0) angle += 2 * PI;

		return -angle;
	}

	static bool rayCrossPointRayed(float3 origin, float3 end, float3 point)
	{
		float3 vec = end - origin;
		float3 normal = mymath::normalize(vec);
		float distance = mymath::getLength(vec);
		float t = 0;

		if (normal.x != 0)
			t = (point.x - origin.x) / normal.x;
		else if (normal.y != 0)
			t = (point.y - origin.y) / normal.y;
		else if (normal.z != 0)
			t = (point.z - origin.z) / normal.z;
		else
			return false;

		if (t >= 0 && t <= distance)
			return true;
		else
			return false;
	}

	static bool pointIntersected(float3 origin, float3 end, float3 point, float pointRadius)
	{
		float denomX = (end.x - origin.x);
		float denomY = (end.y - origin.y);
		float denomZ = (end.z - origin.z);


		if (denomX == 0)
			if (point.x != end.x)
				return false;

		if (denomY == 0)
			if (point.y != end.y)
				return false;

		if (denomZ == 0)
			if (point.z != end.z)
				return false;

		float tx = 0;
		float ty = 0;
		float tz = 0;
		float t = 0;

		if (denomX == 0 && denomY == 0 && denomZ == 0) // 0 0 0 S8
			return false;

		if (denomX == 0 && denomY != 0 && denomZ != 0) // 0 1 1 S1
		{
			ty = (point.y - origin.y) / denomY;
			tz = (point.z - origin.z) / denomZ;
			t = ty;
		}

		if (denomX != 0 && denomY == 0 && denomZ != 0) // 1 0 1 S2
		{
			tx = (point.x - origin.x) / denomX;
			tz = (point.z - origin.z) / denomZ;
			t = tx;
		}

		if (denomX != 0 && denomY != 0 && denomZ == 0) // 1 1 0 S3
		{
			tx = (point.x - origin.x) / denomX;
			ty = (point.y - origin.y) / denomY;
			t = tx;
		}

		if (denomX == 0 && denomY == 0 && denomZ != 0) // 0 0 1 S4
		{
			tz = (point.z - origin.z) / denomZ;
			t = tz;
		}

		if (denomX == 0 && denomY != 0 && denomZ == 0) // 0 1 0 S5
		{
			ty = (point.y - origin.y) / denomY;
			t = ty;
		}

		if (denomX != 0 && denomY == 0 && denomZ == 0) // 1 0 0 S6
		{
			tx = (point.x - origin.x) / denomX;
			t = tx;
		}

		if (denomX != 0 && denomY != 0 && denomZ != 0) // 1 1 1 S7
		{
			tx = (point.x - origin.x) / denomX;
			ty = (point.y - origin.y) / denomY;
			tz = (point.z - origin.z) / denomZ;
			t = tx;
		}

		float3 foundPoint = origin + (end - origin) * t;
		float distance = mymath::getLength(point - foundPoint);
		if (distance <= pointRadius)
			if (t >= 0 && t <= 1)
				return true;
	}

	static float addIn(float resultValue, float time, double deltaTime)
	{
		return (deltaTime / time) * resultValue;
	}

	static float4 getColor(float4 color)
	{
		return float4{color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.z / 255.0f };
	}
};

struct Vertex
{
	float3 pos;
	float2 texCoord;
	float3 normal;
	float3 tangent;
	float3 bitangent;
};

