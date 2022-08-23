#include "pch.h"
#include "BoxCollider.h"
#include "DirectXMath.h"

using namespace DirectX;

BoxCollider::BoxCollider(float3 origin, float3 position, float3 size)
{
	setOrigin(origin);
	setPosition(position);
	setScale(size);
}

bool BoxCollider::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	colliderState.state = modelMatrix * colliderState.state;
	XMMATRIX rotationMatrix = colliderState.state;
	rotationMatrix.r[0] = XMVectorSet(XMVectorGetX(rotationMatrix.r[0]), XMVectorGetY(rotationMatrix.r[0]), XMVectorGetZ(rotationMatrix.r[0]), 0);
	rotationMatrix.r[1] = XMVectorSet(XMVectorGetX(rotationMatrix.r[1]), XMVectorGetY(rotationMatrix.r[1]), XMVectorGetZ(rotationMatrix.r[1]), 0);
	rotationMatrix.r[2] = XMVectorSet(XMVectorGetX(rotationMatrix.r[2]), XMVectorGetY(rotationMatrix.r[2]), XMVectorGetZ(rotationMatrix.r[2]), 0);
	rotationMatrix.r[3] = XMVectorSet(0, 0, 0, 0);


	if (GetAsyncKeyState('P'))
		int point = 0;

	//Получение базиса куба
	XMVECTOR XMtangent   = { 1, 0, 0 };
	XMVECTOR XMnormal    = { 0, 1, 0 };
	XMVECTOR XMbitangent = { 0, 0, 1 };

	XMtangent   = XMVector3Transform(XMtangent,   rotationMatrix);
	XMnormal    = XMVector3Transform(XMnormal,    rotationMatrix);
	XMbitangent = XMVector3Transform(XMbitangent, rotationMatrix);

	float3 tangent   = { XMVectorGetX(XMtangent),   XMVectorGetY(XMtangent),   XMVectorGetZ(XMtangent)   };
	float3 normal    = { XMVectorGetX(XMnormal),    XMVectorGetY(XMnormal),    XMVectorGetZ(XMnormal)    };
	float3 bitangent = { XMVectorGetX(XMbitangent), XMVectorGetY(XMbitangent), XMVectorGetZ(XMbitangent) };

	tangent   = mymath::normalize(tangent);
	normal    = mymath::normalize(normal);
	bitangent = mymath::normalize(bitangent);

	//Получение точек плоскостей
	float3 boxSize = getScale();

	XMVECTOR XMposition = {};
	XMposition = XMVector3Transform(XMposition, colliderState.state);

	float3 boxPosition		   = {XMVectorGetX(XMposition), XMVectorGetY(XMposition), XMVectorGetZ(XMposition)}; //Изначальная точка коробки
	float3 boxPositionDiagonal = boxPosition + tangent * boxSize.x + normal * boxSize.y + bitangent * boxSize.z; //Диагональная точка коробки

	//Описание плоскостей
	struct Plane
	{
		float3 position;
		float3 normal;
	};

	Plane plane[6];

	//Задняя плоскость
	plane[0].position = boxPosition;
	//plane[0].normal   = bitangent * -1;
	plane[0].normal   = bitangent * -1;

	//Передняя плоскость
	plane[1].position = boxPositionDiagonal;
	plane[1].normal   = bitangent;


	//Левая плоскость
	plane[2].position = boxPosition;
	plane[2].normal   = tangent * -1;

	//Правая плоскость
	plane[3].position = boxPositionDiagonal;
	plane[3].normal	  = tangent;


	//Нижняя плоскость
	plane[4].position = boxPosition;
	plane[4].normal   = normal * -1;

	//Верхняя плоскость
	plane[5].position = boxPositionDiagonal;
	plane[5].normal   = normal;



	//Нахождение точек пересечения плоскостей
	RayHitPoint boxHitPoint[6];
	for (int x = 0; x < 6; x++)
	{
		double div = plane[x].normal.x * ray.direction.x + plane[x].normal.y * ray.direction.y + plane[x].normal.z * ray.direction.z;
		boxHitPoint[x].intersect = div != 0;

		if (div != 0)
		{
			double t = (plane[x].normal.x * (plane[x].position.x - ray.position.x) + plane[x].normal.y * (plane[x].position.y - ray.position.y) + plane[x].normal.z * (plane[x].position.z - ray.position.z)) / div;
			boxHitPoint[x].distance = t;
			boxHitPoint[x].position = ray.position + ray.direction * t;
		}
	}

	//Определение пересечения коробки
	double minDistance = 999999;
	bool intersect = false;

	for (int x = 0; x < 6; x++)
	{
		if (true)
		{
			if (boxHitPoint[x].intersect)
			{
				bool inBox = true;
				for (int y = 0; y < 6; y++)
				{
					double k = plane[y].normal.x * (boxHitPoint[x].position.x - plane[y].position.x) +
							  plane[y].normal.y * (boxHitPoint[x].position.y - plane[y].position.y) +
							  plane[y].normal.z * (boxHitPoint[x].position.z - plane[y].position.z);
					inBox = k <= 0.000001;
					if (!inBox)
						break;
				}

				if (inBox && boxHitPoint[x].distance <= minDistance)
				{
					*hitPoint = boxHitPoint[x];
					minDistance = boxHitPoint[x].distance;
					intersect = true;
				}
			}
		}
	}

	 return intersect;
}