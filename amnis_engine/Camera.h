#pragma once
#include "Graphics.h"
#include "mymath.h"
#include <DirectXMath.h>
#include "MainWindow.h"
#include "decl.h"
#include "Ray.h"

class RenderWindow;


class Camera
{
public:
	float3 position;
	float3 rotation;
	float3 velocity = {};
	float accelirationSpeed = 0.1f;
	float maxSpeedTime = 0.05f;
	float minSpeedTime = 0.1f;
	float moveSpeed = 30.0f;
	double rotationSpeed = 3.5f;
	bool responded;

	float aspect = 1;
	float fov = 3.14f / 2;
	float angle = 1 / std::tan(fov / 2);
	float znear = 0.01f;
	float zfar = 10000.0f;

	float3 tangent = {0, 0, 1};
	float3 bitangent = {1, 0, 0};
	float3 normal = {0, 1, 0};


	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
	DECL Camera(RenderWindow* renderWindow, float3 camPos, float3 camRotation, bool responded);
	DECL Camera(RenderWindow* renderWindow, bool responded);
	DECL virtual void update();
	DECL virtual void responseInput(MainWindow* mainWindow);
	DECL void setPerspectiveCoof(float value);
	DECL Ray castRay(float pX, float pY);
	DECL Ray castRayFromMouse();

protected:
	RenderWindow* renderWindow;
	float perspectiveCoof = 0;
};

