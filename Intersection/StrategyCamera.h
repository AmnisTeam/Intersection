#pragma once
#include "Camera.h"
class StrategyCamera : public Camera
{
public:
	StrategyCamera();
	StrategyCamera(float3 camPos, float3 camRotation);

	virtual void responseInput(Graphics* graphics, MainWindow* mainWindow) override;
};

