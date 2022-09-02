#pragma once
#include "Camera.h"
#include <iostream>

class StrategyCamera : public Camera
{
public:
	float3 lookPoint = { 0, 0, 0 };
	float radius = 10;
	float speedRotation = 0.01f;
	float speedChangeRadius = 0.1f;
	float velocityRotation = 0;
	float velocityRadius = 0;
	float velocityTimeMin = 0.2f;
	float tempWheelDelta = 0;

	StrategyCamera(RenderWindow* renderWindow);
	StrategyCamera(RenderWindow* renderWindow, float3 camPos, float3 camRotation);

	virtual void responseInput(MainWindow* mainWindow) override;
	virtual void update();
};

