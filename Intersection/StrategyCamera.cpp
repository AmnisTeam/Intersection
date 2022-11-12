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

	if (mainWindow->mouse.GetPosX() <= rect.left) // Left
	{//renderWindow->window->mouse.GetPosX()
		velocity += { -tickIncreaseSpeed, 0, 0 };
		moved = true;
	}

	if (mainWindow->mouse.GetPosX() >= rect.right - 1) // Right
	{
		velocity += { tickIncreaseSpeed, 0, 0 };
		moved = true;
	}

	if (mainWindow->mouse.GetPosY() <= rect.top) // Top
	{
		velocity += { 0, 0, tickIncreaseSpeed };
		moved = true;
	}

	if (mainWindow->mouse.GetPosY() >= rect.bottom - 1) // Bottom
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

	lookPoint += velocity * renderWindow->graphics->deltaTime;


	if (renderWindow->window->mouse.GetWheelDelta() != 0)
	{
		tempWheelDelta = renderWindow->window->mouse.GetWheelDelta() > 0 ? 1 : -1;
	}

	velocityRotation = mymath::toValue(
		velocityRotation, 
		tempWheelDelta * speedRotation,
		speedRotation * renderWindow->graphics->deltaTime / velocityTimeMin);

	velocityRadius = mymath::toValue(
		velocityRadius, 
		tempWheelDelta * speedChangeRadius,
		speedChangeRadius * renderWindow->graphics->deltaTime / velocityTimeMin);

	if (abs(velocityRotation) == speedRotation && abs(velocityRadius) == speedChangeRadius)
		tempWheelDelta = 0;

	rotation.x -= velocityRotation;
	radius -= velocityRadius;

	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(0, 0, -radius) *
		DirectX::XMMatrixRotationX(rotation.x) *
		DirectX::XMMatrixRotationY(rotation.y) *
		DirectX::XMMatrixRotationZ(rotation.z) *
		DirectX::XMMatrixTranslation(lookPoint.x, lookPoint.y, lookPoint.z);

	DirectX::XMVECTOR XMPosition = DirectX::XMVector3Transform(DirectX::XMVECTOR(), matrix);
	position = { DirectX::XMVectorGetX(XMPosition), DirectX::XMVectorGetY(XMPosition) , DirectX::XMVectorGetZ(XMPosition) };
}

void StrategyCamera::update()
{
	Camera::update();
}
