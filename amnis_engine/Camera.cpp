#include "pch.h"
#include "Camera.h"

Camera::Camera(float3 camPos, float3 camRotation, bool responded)
{
	this->responded = responded;
	this->position = camPos;
	this->rotation = camRotation;
	viewMatrix = DirectX::XMMatrixIdentity();
	projectionMatrix = DirectX::XMMatrixIdentity();
}

Camera::Camera(bool responded)
{
	this->responded = responded;
	position = {};
	rotation = {};
	viewMatrix = DirectX::XMMatrixIdentity();
	projectionMatrix = DirectX::XMMatrixIdentity();
}

void Camera::update(Graphics* graphics)
{
	RECT clientRect{};
	GetClientRect(graphics->hwnd, &clientRect);
	viewMatrix = DirectX::XMMatrixTranslation(-position.x, -position.y, -position.z) * DirectX::XMMatrixRotationY(-rotation.x) * DirectX::XMMatrixRotationX(-rotation.y);
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(0.4 * 3.14, (float)clientRect.right / clientRect.bottom, 0.1f, 100000);
}

void Camera::responseInput(Graphics* graphics, MainWindow* mainWindow)
{
	if (mainWindow->rawMouseDelta.x)
		int k = 5;
	rotation.x += (double)mainWindow->rawMouseDelta.x * rotationSpeed * graphics->deltaTime;
	rotation.y += (double)mainWindow->rawMouseDelta.y * rotationSpeed * graphics->deltaTime;

	DirectX::XMVECTOR tangent = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMMatrixRotationX(rotation.y) * DirectX::XMMatrixRotationY(rotation.x));
	DirectX::XMVECTOR binormal = DirectX::XMVector3Transform(DirectX::XMVectorSet(1, 0, 0, 0), DirectX::XMMatrixRotationX(rotation.y) * DirectX::XMMatrixRotationY(rotation.x));
	float tickIncreaseSpeed = (graphics->deltaTime / maxSpeedTime) * moveSpeed;
	bool moved = false;
	if (GetAsyncKeyState('W'))
	{
		velocity.x += DirectX::XMVectorGetX(tangent) * tickIncreaseSpeed;
		velocity.y += DirectX::XMVectorGetY(tangent) * tickIncreaseSpeed;
		velocity.z += DirectX::XMVectorGetZ(tangent) * tickIncreaseSpeed;
		moved = true;
	}
	if (GetAsyncKeyState('D'))
	{
		velocity.x += DirectX::XMVectorGetX(binormal) * tickIncreaseSpeed;
		velocity.y += DirectX::XMVectorGetY(binormal) * tickIncreaseSpeed;
		velocity.z += DirectX::XMVectorGetZ(binormal) * tickIncreaseSpeed;
		moved = true;
	}
	if (GetAsyncKeyState('S'))
	{
		velocity.x -= DirectX::XMVectorGetX(tangent) * tickIncreaseSpeed;
		velocity.y -= DirectX::XMVectorGetY(tangent) * tickIncreaseSpeed;
		velocity.z -= DirectX::XMVectorGetZ(tangent) * tickIncreaseSpeed;
		moved = true;
	}
	if (GetAsyncKeyState('A'))
	{
		velocity.x -= DirectX::XMVectorGetX(binormal) * tickIncreaseSpeed;
		velocity.y -= DirectX::XMVectorGetY(binormal) * tickIncreaseSpeed;
		velocity.z -= DirectX::XMVectorGetZ(binormal) * tickIncreaseSpeed;
		moved = true;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		position.y += moveSpeed * graphics->deltaTime;
	}

	if (GetAsyncKeyState(VK_SHIFT))
	{
		position.y -= moveSpeed * graphics->deltaTime;
	}

	float tickDecreasSpeed = (graphics->deltaTime / minSpeedTime) * moveSpeed;
	if (!moved)
	{
		float length = mymath::getLength(velocity);
		if (length - tickDecreasSpeed < 0)
			velocity = { 0, 0, 0 };
		else
			velocity -= mymath::normalize(velocity) * tickDecreasSpeed;
	}

	if (mymath::getLength(velocity) > moveSpeed)
		mymath::setLength(&velocity, moveSpeed);

	position += velocity * graphics->deltaTime;
}
