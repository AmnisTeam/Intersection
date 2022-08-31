#include "pch.h"
#include "CompositeCollider.h"

using namespace DirectX;

CompositeCollider::CompositeCollider()
{
}

void CompositeCollider::addCollider(Collider* collider)
{
	colliders.push_back(collider);
}

void CompositeCollider::setPosition(float3 position)
{
	Transformable::setPosition(position);
}

void CompositeCollider::setRotation(float3 rotation)
{
	Transformable::setRotation(rotation);
}

void CompositeCollider::setScale(float3 scale)
{
	Transformable::setScale(scale);
}

void CompositeCollider::setOrigin(float3 origin)
{
	Transformable::setOrigin(origin);
}

bool CompositeCollider::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	colliderState.state = modelMatrix * colliderState.state;
	bool intersect = false;
	//float3 minHitPoint = {};
	//float minDistance = 99999999;
	//for (int x = 0; x < colliders.size(); x++)
	//{
	//	float3 tempPosition = colliders[x]->getPosition();
	//	float3 tempScale = colliders[x]->getScale();
	//	float3 tempOrigin = colliders[x]->getOrigin();
	//	float3 tempRotation = colliders[x]->getRotation();

	//	XMVECTOR XMtangent = { 1, 0, 0 };
	//	XMVECTOR XMnormal = { 0, 1, 0 };
	//	XMVECTOR XMbitangent = { 0, 0, 1 };

	//	XMtangent = XMVector3Transform(XMtangent, XMMatrixRotationX(tempRotation.x) * XMMatrixRotationY(tempRotation.y) * XMMatrixRotationZ(tempRotation.z));
	//	XMnormal = XMVector3Transform(XMnormal, XMMatrixRotationX(tempRotation.x) * XMMatrixRotationY(tempRotation.y) * XMMatrixRotationZ(tempRotation.z));
	//	XMbitangent = XMVector3Transform(XMbitangent, XMMatrixRotationX(tempRotation.x) * XMMatrixRotationY(tempRotation.y) * XMMatrixRotationZ(tempRotation.z));


	//	float3 hitPoint;
	//	bool temp = colliders[x]->raycast(ray, &hitPoint);
	//	if (temp)
	//	{
	//		float distance = mymath::getLength(hitPoint - ray.position);
	//		if (distance < minDistance)
	//		{
	//			minDistance = distance;
	//			minHitPoint = hitPoint;
	//		}
	//	}
	//	if (!intersect)
	//		intersect = temp;
	//}

	//if (intersect)
	//	*hitPoint = minHitPoint;

	return intersect;
}
