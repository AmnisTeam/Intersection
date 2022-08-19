#include "StrategyCamera.h"
#include "RenderWindow.h"

StrategyCamera::StrategyCamera(RenderWindow* renderWindow) : Camera(renderWindow, false)
{

}

StrategyCamera::StrategyCamera(RenderWindow* renderWindow, float3 camPos, float3 camRotation) : Camera(renderWindow, camPos, camRotation, false)
{

}

void StrategyCamera::responseInput(MainWindow* mainWindow)
{
	RECT rect;
	GetClientRect(mainWindow->hwnd, &rect);


	DirectX::XMVECTOR tangent = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));
	DirectX::XMVECTOR binormal = DirectX::XMVector3Transform(DirectX::XMVectorSet(1, 0, 0, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));
	DirectX::XMVECTOR normal = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));

	this->tangent = { DirectX::XMVectorGetX(tangent), DirectX::XMVectorGetY(tangent) , DirectX::XMVectorGetZ(tangent) };
	this->bitangent = { DirectX::XMVectorGetX(binormal), DirectX::XMVectorGetY(binormal) , DirectX::XMVectorGetZ(binormal) };
	this->normal = { DirectX::XMVectorGetX(normal), DirectX::XMVectorGetY(normal) , DirectX::XMVectorGetZ(normal) };



	float tickIncreaseSpeed = (renderWindow->graphics->deltaTime / maxSpeedTime) * moveSpeed;
	bool moved = false;

	if (mainWindow->mousePos.x <= rect.left) // Left
	{
		velocity += { -tickIncreaseSpeed, 0, 0 };
		moved = true;
	}

	if (mainWindow->mousePos.x >= rect.right - 1) // Right
	{
		velocity += { tickIncreaseSpeed, 0, 0 };
		moved = true;
	}

	if (mainWindow->mousePos.y <= rect.top) // Top
	{
		velocity += { 0, 0, tickIncreaseSpeed };
		moved = true;
	}

	if (mainWindow->mousePos.y >= rect.bottom - 1) // Bottom
	{
		velocity += { 0, 0, -tickIncreaseSpeed };
		moved = true;
	}


	float tickDecreasSpeed = (renderWindow->graphics->deltaTime / minSpeedTime) * moveSpeed;

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

	position += velocity * renderWindow->graphics->deltaTime;
}
