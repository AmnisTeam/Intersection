#pragma once
#include <iostream>
#include <DirectXMath.h>
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

	float2 operator/(float val)
	{
		return float2{ x / val, y / val};
	}

	float2 operator*(float val)
	{
		return float2{ x * val, y * val };
	}

	void operator/=(float val)
	{
		x /= val;
		y /= val;
	}

	void operator*=(float val)
	{
		x *= val;
		y *= val;
	}

	void operator+=(float2 vec)
	{
		x += vec.x;
		y += vec.y;
	}

	void operator-=(float2 vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	float2 operator-(float2 vec) const
	{
		return { x - vec.x, y - vec.y};
	}

	float2 operator+(float2 vec) const
	{
		return { x + vec.x, y + vec.y};
	}

	bool operator!=(float2 const vec) const
	{
		if (x != vec.x || y != vec.y)
			return true;
		else
			return false;
	}
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

	bool operator==(float3 const vec) const
	{
		if (x == vec.x && y == vec.y && z == vec.z)
			return true;
		else
			return false;
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

struct Vertex
{
	float3 pos;
	float2 texCoord;
	float3 normal;
	float3 tangent;
	float3 bitangent;
};

struct int2
{
	int x;
	int y;
};

struct int3
{
	int x;
	int y;
	int z;
};

struct BazierPoint
{
	float2 position;
	float2 direction;
	float radius;
};

class mymath
{
public:
	static float getLength(float2 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	static float getLength(float3 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	static double getLength(double3 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	static float2 normalize(float2 vec)
	{
		if (vec.x == 0 && vec.y == 0)
			return { 0, 0 };
		else
			return vec / getLength(vec);
	}

	static float3 normalize(float3 vec)
	{
		if (vec.x == 0 && vec.y == 0 && vec.z == 0)
			return {0, 0, 0};
		else
			return vec / getLength(vec);
	}

	static double3 normalize(double3 vec)
	{
		if (vec.x == 0 && vec.y == 0 && vec.z == 0)
			return { 0, 0, 0 };
		else
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

	static float toValue(float from, float to, float speed)
	{
		speed = from > to ? -abs(speed) : abs(speed);
		if ((from - to) / (from - to + speed) <= 0)
			return to;
		else
			return from + speed;
	}

	static float2 getBazierValue(float t, float2* points, int countPoints)
	{
		float2 point;
		float2* pointsOnLine = new float2[countPoints - 1];
		for (int x = 0; x < countPoints - 1; x++)
			pointsOnLine[x] = points[x] + (points[x + 1] - points[x]) * t;

		if (countPoints == 1)
			point = pointsOnLine[0];
		else
			point = getBazierValue(t, pointsOnLine, countPoints - 1);
		delete[countPoints - 1] pointsOnLine;

		return point;
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
		if (point == end)
			return true;

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

	static DirectX::XMMATRIX getRotation(float3 direction)
	{
		//float3 oyv = normalize(float3{ direction.x, 0, direction.z });
		//float3 oxv = normalize(float3{ 0, direction.y, direction.z });
		//float3 ozv = normalize(float3{ direction.x, direction.y, 0 });

		//float angleY = ((getLength(oyv) != 0) ? (acos(oyv.x) * (oyv.z >= 0 ? 1 : -1)) : 0);
		////float angleX = (getLength(oxv) != 0) ? (acos(oxv.z) * (oxv.y >= 0 ? 1 : -1)) : 0;
		//float angleX = PI / 2 - acos(direction.y);
		//float angleZ = (getLength(ozv) != 0) ? (acos(ozv.x) * (ozv.y >= 0 ? 1 : -1)) : 0;




		//float phi = direction.y * PI / 2;
		//float theta = acos(direction.x / (1 - direction.y));
		//float tz = sin(theta) * (1 - (2 * phi) / PI);
		//if (direction.z > tz - 0.01f && direction.z < tz + 0.01f)
		//	theta = -theta;

		//float3 v = direction;
		//float3 p = {1, 0, 0};

		//float b1 = 2 * atan(v.x / p.z);
		//float b2 = -2 * atan(sqrt(p.z * p.z - v.x * v.x + p.x * p.x) / (v.x + p.x) - p.z / (v.x + p.x));
		//float b3 = 2 * atan(sqrt(p.z * p.z - v.x * v.x + p.x * p.x) / (v.x + p.x) + p.z / (v.x + p.x))

		//float a1 = -2 * atan(p.y / (p.x * sin(b1) - p.z * cos(b1)));

		float b = asin(direction.y);
		float a = acos(direction.x / cos(b));

		if (sin(a) * cos(b) > direction.z - 0.001f && sin(a) * cos(b) < direction.z + 0.001f)
			return DirectX::XMMatrixRotationY(-a) * DirectX::XMMatrixRotationZ(b) * DirectX::XMMatrixRotationY(a) * DirectX::XMMatrixRotationY(a);

		a = -a;

		if (sin(a) * cos(b) > direction.z - 0.001f && sin(a) * cos(b) < direction.z + 0.001f)
			return DirectX::XMMatrixRotationY(-a) * DirectX::XMMatrixRotationZ(b) * DirectX::XMMatrixRotationY(a) * DirectX::XMMatrixRotationY(a);

		b = PI - b;
		a = acos(direction.x / cos(b));

		if (sin(a) * cos(b) > direction.z - 0.001f && sin(a) * cos(b) < direction.z + 0.001f)
			return DirectX::XMMatrixRotationY(-a) * DirectX::XMMatrixRotationZ(b) * DirectX::XMMatrixRotationY(a) * DirectX::XMMatrixRotationY(a);

		a = -a;

		if (sin(a) * cos(b) > direction.z - 0.001f && sin(a) * cos(b) < direction.z + 0.001f)
			return DirectX::XMMatrixRotationY(-a) * DirectX::XMMatrixRotationZ(b) * DirectX::XMMatrixRotationY(a) * DirectX::XMMatrixRotationY(a);
	}
};

