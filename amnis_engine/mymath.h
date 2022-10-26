#pragma once
#include <iostream>
#include <DirectXMath.h>
#include <vector>
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

class FloatRect
{
public:
	float2 position;
	float2 size;

	FloatRect(float2 position, float2 size)
	{
		this->position = position;
		this->size = size;
	}

	FloatRect(float pX, float pY, float sizeX, float sizeY)
	{
		this->position = { pX, pY };
		this->size = { sizeX, sizeY };
	}

	bool intersect(FloatRect& rect) const
	{
		if (position.x + size.x >= rect.position.x && position.x <= rect.position.x + rect.size.x)
			if (position.y + size.y >= rect.position.y && position.y <= rect.position.y + rect.size.y)
				return true;
		return false;
	}

	void collision(float2 deltaPosition, FloatRect& rect)
	{
		float2 offset = {};
		if (position.y + size.y < rect.position.y + deltaPosition.y)
			offset.y = -deltaPosition.y;

		if (position.y > rect.position.y + rect.size.y + deltaPosition.y)
			offset.y = -deltaPosition.y;

		if (position.x + size.x < rect.position.x + deltaPosition.x)
			offset.x = -deltaPosition.x;

		if (position.x > rect.position.x + rect.size.x + deltaPosition.x)
			offset.x = -deltaPosition.x;

		position += offset;
	}
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

	static DirectX::XMMATRIX getLookAtMatrix(float3 direction)
	{
		return DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 0, 0, 0), DirectX::XMVectorSet(direction.x, direction.y, direction.z, 0), DirectX::XMVectorSet(0, 1, 0, 0));
	}

	static float dot(float3 a, float3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static float3 circleLerp(float3 a, float3 b, float teta)
	{
		float la = mymath::getLength(a);
		float lb = mymath::getLength(b);

		a = mymath::normalize(a);
		b = mymath::normalize(b);

		float angle = acos(a.x * b.x + a.y * b.y + a.z * b.z);
		float lc = la + (lb - la) * (teta / angle);

		float alpha = teta;
		float beta = angle - alpha;

		float3 d = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
		float detA = a.x * b.y * d.z + a.y * b.z * d.x + b.x * d.y * a.z - a.z * b.y * d.x - a.y * b.x * d.z - b.z * d.y * a.x;
		float cx = ((b.y * d.z - b.z * d.y) * cos(alpha) + (a.z * d.y - a.y * d.z) * cos(beta)) / detA;
		float cy = ((b.z * d.x - b.x * d.z) * cos(alpha) + (a.x * d.z - a.z * d.x) * cos(beta)) / detA;
		float cz = ((b.x * d.y - b.y * d.x) * cos(alpha) + (a.y * d.x - a.x * d.y) * cos(beta)) / detA;
		return { cx, cy, cz };
	}

	private:
	struct restLineData { int2* path; int id; };
	static void restLineAction(int x, int y, void* data)
	{
		int2* path = (int2*)data;
		
	}

	public:
	//Количество вызовов будет равно max(p2.x - p1.x + 1, p2.y - p1.y + 1) * 3
	static void restLine(float2 p1, float2 p2, std::vector<int2>& path, int* size)
	{
		*size = 0;
		int id = 0;
		double deltaX = abs(p2.x - p1.x) + 1;
		double deltaY = abs(p2.y - p1.y) + 1;
		double k = deltaY < deltaX ? deltaY / deltaX : deltaX / deltaY;
		int signX = p2.x - p1.x >= 0 ? 1 : -1;
		int signY = p2.y - p1.y >= 0 ? 1 : -1;

		if (deltaY < deltaX)
		{
			double y = 0;
			for (int x = 0; x < (int)deltaX; x++)
			{
				float px = p1.x + x * signX;
				float py = p1.y + y * signY;
				for (int i = -1; i <= 1; i++)
				{
					if (id >= path.size())
						path.push_back({});

					path[id].x = px < 0 ? floor(px) : px;
					path[id].y = (py < 0 ? floor(py) : py) + i;
					id++;
					(*size)++;
				}
				y += k;
			}
		}
		else
		{
			double x = 0;
			for (int y = 0; y < (int)deltaY; y++)
			{
				float px = p1.x + x * signX;
				float py = p1.y + y * signY;
				for (int i = -1; i <= 1; i++)
				{
					if (id >= path.size())
						path.push_back({});

					path[id].x = (px < 0 ? floor(px) : px) + i;
					path[id].y = py < 0 ? floor(py) : py;
					id++;
					(*size)++;
				}
				x += k;
			}
		}
	}

	static int2 getGridId(float3 point, float2 sizeGrid)
	{
		int endX = (float)point.x / sizeGrid.x;
		int endZ = (float)point.z / sizeGrid.y;

		endX = point.x <= 0 ? endX - 1 : endX;
		endZ = point.z <= 0 ? endZ - 1 : endZ;

		endZ++;

		return {endX, endZ};
	}
};

