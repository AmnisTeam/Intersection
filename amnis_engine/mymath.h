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

	static float3 normalize(float3 vec)
	{
		return vec / getLength(vec);
	}

	static void setLength(float3* vec, float length)
	{
		*vec = normalize(*vec) * length;
	}

	//static double changeIn(double changedValue, double changeToValue, double deltaTime)
	//{
	//	(deltaTime / maxSpeedTime)* changeToValue;
	//}
};

struct Vertex
{
	float3 pos;
	float2 texCoord;
	float3 normal;
	float3 tangent;
	float3 bitangent;
};

