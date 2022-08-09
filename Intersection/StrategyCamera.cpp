#include "StrategyCamera.h"

StrategyCamera::StrategyCamera() : Camera(false)
{

}

StrategyCamera::StrategyCamera(float3 camPos, float3 camRotation) : Camera(camPos, camRotation, false)
{

}

void StrategyCamera::responseInput(Graphics* graphics, MainWindow* mainWindow)
{
	RECT rect;
	GetClientRect(mainWindow->hwnd, &rect);

	float tickIncreaseSpeed = (graphics->deltaTime / maxSpeedTime) * moveSpeed;
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
