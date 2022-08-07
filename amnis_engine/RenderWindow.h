#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "IDrawable.h"
#include "RenderTarget.h"
#include <chrono>
#include "ModelsContent.h"
#include "decl.h"

class RenderWindow
{
public:
	MainWindow* window;
	Graphics* graphics;
	Camera* boundCamera;
	ModelsContent* modelsContent;
	bool isOpen = true;

	DECL RenderWindow();
	DECL ~RenderWindow();
	DECL void Draw(IDrawable* object, bool depthStencilOn = true);
	DECL void display();
	DECL void update();
	DECL void dispatchEvents();
	DECL void clear(float4 color);
	DECL void updatePointLights();
	DECL void setCamera(Camera* camera);
	DECL void startDeltaTime();
	DECL void endDeltaTime();
	DECL void setBackRenderTargetAndDepthStencil();
private:
	MSG msg;
	std::chrono::steady_clock::time_point start;
};