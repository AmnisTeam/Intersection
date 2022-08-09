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

	static bool rayCrossPoint(float3 origin, float3 end, float3 point)
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

	static float addIn(float resultValue, float time, double deltaTime)
	{
		return (deltaTime / time) * resultValue;
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

