#pragma once
#include "Camera.h"

class StrategyCamera : public Camera
{
public:
	StrategyCamera(RenderWindow* renderWindow);
	StrategyCamera(RenderWindow* renderWindow, float3 camPos, float3 camRotation);

	virtual void responseInput(Graphics* graphics, MainWindow* mainWindow) override;
};

