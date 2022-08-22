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

bool BoxCollider::raycast(float3 rayOrigin, float3 rayDirection, float3* hitPoint)
{
	if (GetAsyncKeyState('P'))
		int point = 0;

	//Получение базиса куба
	float3 notRotatedOrigin	= getOrigin();
	float3 rotation = getRotation();
	XMVECTOR XMtangent   = { 1, 0, 0 };
	XMVECTOR XMnormal    = { 0, 1, 0 };
	XMVECTOR XMbitangent = { 0, 0, 1 };
	XMVECTOR XMOrigin	 = { notRotatedOrigin.x, notRotatedOrigin.y, notRotatedOrigin.z};

	XMtangent   = XMVector3Transform(XMtangent,   XMMatrixRotationX(rotation.x) * XMMatrixRotationY(rotation.y) * XMMatrixRotationZ(rotation.z));
	XMnormal    = XMVector3Transform(XMnormal,    XMMatrixRotationX(rotation.x) * XMMatrixRotationY(rotation.y) * XMMatrixRotationZ(rotation.z));
	XMbitangent = XMVector3Transform(XMbitangent, XMMatrixRotationX(rotation.x) * XMMatrixRotationY(rotation.y) * XMMatrixRotationZ(rotation.z));
	XMOrigin	= XMVector3Transform(XMOrigin,    XMMatrixRotationX(rotation.x) * XMMatrixRotationY(rotation.y) * XMMatrixRotationZ(rotation.z));

	float3 tangent   = { XMVectorGetX(XMtangent),   XMVectorGetY(XMtangent),   XMVectorGetZ(XMtangent)   };
	float3 normal    = { XMVectorGetX(XMnormal),    XMVectorGetY(XMnormal),    XMVectorGetZ(XMnormal)    };
	float3 bitangent = { XMVectorGetX(XMbitangent), XMVectorGetY(XMbitangent), XMVectorGetZ(XMbitangent) };
	float3 origin    = { XMVectorGetX(XMOrigin),    XMVectorGetY(XMOrigin),    XMVectorGetZ(XMOrigin)    };

	//Получение точек плоскостей
	float3 boxSize = getScale();

	float3 boxPosition         = getPosition() + origin; //Изначальная точка коробки
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
	struct HitPoint
	{
		bool intersect;
		float3 position;
		double distance;
	};

	HitPoint boxHitPoint[6];
	for (int x = 0; x < 6; x++)
	{
		double div = plane[x].normal.x * rayDirection.x + plane[x].normal.y * rayDirection.y + plane[x].normal.z * rayDirection.z;
		boxHitPoint[x].intersect = div != 0;

		if (div != 0)
		{
			double t = (plane[x].normal.x * (plane[x].position.x - rayOrigin.x) + plane[x].normal.y * (plane[x].position.y - rayOrigin.y) + plane[x].normal.z * (plane[x].position.z - rayOrigin.z)) / div;
			boxHitPoint[x].distance = t;
			boxHitPoint[x].position = rayOrigin + rayDirection * t;
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
					*hitPoint = boxHitPoint[x].position;
					minDistance = boxHitPoint[x].distance;
					intersect = true;
				}
			}
		}
	}

	 return intersect;
}