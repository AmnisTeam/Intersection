#include "pch.h"
#include "Transformable.h"

void Transformable::setPosition(float3 position)
{
	this->position = position;
	updateModelMatrix();
}

void Transformable::setRotation(float3 rotation)
{
	this->rotation = rotation;
	updateModelMatrix();
}

void Transformable::setScale(float3 scale)
{
	this->scale = scale;
	updateModelMatrix();
}

float3 Transformable::getPosition() const
{
	return position;
}

float3 Transformable::getRotation() const
{
	return rotation;
}

float3 Transformable::getScale() const
{
	return scale;
}

void Transformable::updateModelMatrix()
{
	modelMatrix = 
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationX(rotation.x) * 
		DirectX::XMMatrixRotationY(rotation.y) *
		DirectX::XMMatrixRotationZ(rotation.z) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z);
}
