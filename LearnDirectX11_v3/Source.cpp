#include "MainWindow.h"
#include "Graphics.h"
#include "Shape.h"
#include "Box.h"
#include "DirectLightSource.h"
#include "Model.h"
#include "Camera.h"
#include "DirectLightSource.h"
#include "PointLight.h"
#include "GameObject.h"
#include "Sphere.h"
#include "TwoBalls.h"
#include <chrono>
#include "Spherenic.h"
#include "ModeledObject.h"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
//{
//	/*
//	RenderWindow window;
//
//	Camera* camera = new Camera();
//	window.setCamera(camera);
//
//	Sphere* sphere = new Sphere();
//	window.Draw(sphere);
//
//	*/
//
//	MainWindow mainWindow;
//	mainWindow->create(L"Main window");
//	Graphics graphics;
//	graphics.initDirectX11(mainWindow.hwnd);
//	graphics.initDepthStencil();
//	ShowWindow(mainWindow.hwnd, nCmdShow);
//	graphics.initTexturesContent();
//
//	//RenderWindow* renderWindow = new RenderWindow();
//
//	Shape shape(&graphics);
//	Shape light(&graphics);
//	Box box = Box(&graphics);
//
//	RAWINPUTDEVICE rid{};
//	rid.usUsagePage = 0x01;
//	rid.usUsage = 0x02;
//	rid.dwFlags = 0;
//	rid.hwndTarget = nullptr;
//
//	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
//		throw;
//
//	Camera mainCamera = Camera();
//	mainCamera.position = { 0, 3, -10 };
//
//	float factor2 = 0.014f;
//	float factor3 = 0.0007f;
//
//	PointLight whitePointLight = PointLight(&graphics, (char*)"Models//sphere.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->lightSourcePS);
//	whitePointLight.setPosition(float3{ 0, 1, -3 });
//	whitePointLight.setColor(float4{ 1, 1, 1, 1 });
//	whitePointLight.setFactors(float3{ 1, factor2, factor3 });
//
//
//	//Model bug = Model(&graphics, (char*) "Models//Graphosoma.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	//bug.setTexture(&bugAlbedo, 0);
//	//bug.setTexture(&stoneWallNormalMap, 1);
//	//bug.position = { 0, 10, 0 };
//
//	Model skySphere = Model(&graphics, (char*)"Models//sphere.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->skyPS);
//	skySphere.setTexture(graphics.texturesContent->textureSky, 0);
//	skySphere.scale = { -100, -100, -100 };
//	skySphere.drawDepthStencil = false;
//
//	Model plane = Model(&graphics, (char*)"Models//Plane.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	plane.setTexture(graphics.texturesContent->stoneWallAlbedo, 0);
//	plane.setTexture(graphics.texturesContent->stoneWallNormalMap, 1);
//	plane.scale = float3{ 1, 1, 1 };
//
//	//Model sponza = Model(&graphics, (char*)"Models\\crytek-sponza-huge-vray-obj\\crytek-sponza-huge-vray.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	//sponza.setTexture(&textureSky, 0);
//	//sponza.setTexture(&flatNormalMap, 1);
//	//sponza.position = {0, -30, -10};
//	//sponza.scale = { 0.2f, 0.2f, 0.2f };
//
//
//	//Model wheelRobot = Model(&graphics, (char*)"Models\\wheeled-robot\\source\\RobotWheel.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	//Model wheelRobot = Model(&graphics, (char*)"Models\\industrial-robot\\source\\armLOW.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	//Model wheelRobot = Model(&graphics, (char*)"Models\\cozy-living-room-baked\\source\\5.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	//Model wheelRobot = Model(&graphics, (char*)"Models\\away-the-survival-series-fox-rigged\\source\\Fox.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	Model wheelRobot = Model(&graphics, (char*)"Models\\mirtyu-the-death-spirit\\source\\All.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	wheelRobot.setTexture(graphics.texturesContent->wheelRobotBaseColor, 0);
//	wheelRobot.setTexture(graphics.texturesContent->wheelRobotNormal, 1);
//
//
//	Model wheelRobotModel = Model(&graphics, (char*)"Models\\wheeled-robot\\source\\RobotWheel.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
//	wheelRobotModel.setTexture(graphics.texturesContent->wheelRobotBaseColor, 0);
//	wheelRobotModel.setTexture(graphics.texturesContent->wheelRobotNormal, 1);
//
//	//GameObject testObj = GameObject(&graphics);
//	//testObj.setModel(&wheelRobotModel);
//	//float color[4] = { 0.4f, 0.6f, 1.0f, 1.0f };
//	float color[4] = { 0, 0, 0, 1.0f };
//	bool gameLoop = true;
//	float tempAngle = 0;
//	RECT clientRect{};
//	GetClientRect(mainWindow.hwnd, &clientRect);
//
//	//Sphere sphereObject = Sphere(&graphics);
//	//TwoBalls twoBalls = TwoBalls(&graphics);
//	//twoBalls.position.z = 5;
//
//	MSG msg{};
//	graphics.setFirstOldClockAndDeltaTime();
//	mainWindow.activateCursor(false);
//	graphics.setCameraToDraw(&mainCamera);
//	while (gameLoop)
//	{
//		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//			if (msg.message == WM_QUIT)
//				gameLoop = false;
//		}
//		if (!gameLoop)
//			break;
//		graphics.updateDeltaTime();
//		mainCamera.responseInput(&graphics, &mainWindow);
//		mainCamera.update(&graphics);
//
//		graphics.deviceCon->ClearRenderTargetView(graphics.backRenderTarget, color);
//
//		graphics.deviceCon->OMSetRenderTargets(1, &graphics.backRenderTarget, NULL);
//		skySphere.position = mainCamera.position;
//		skySphere.draw(&graphics, &mainCamera);
//		graphics.deviceCon->OMSetRenderTargets(1, &graphics.backRenderTarget, graphics.depthStencilView);
//
//		graphics.deviceCon->PSSetShaderResources(9, 1, &graphics.pointLightsSRV);
//		graphics.deviceCon->PSSetConstantBuffers(9, 1, &graphics.lightsCountsBuffer);
//		//textureSky.bind(2);
//
//		tempAngle += 3.14f * graphics.deltaTime;
//
//		plane.draw(&graphics, &mainCamera);
//		whitePointLight.setPosition(float3{ sin(tempAngle) * 2, whitePointLight.position.y, cos(tempAngle) * 2 });
//		whitePointLight.draw(&graphics, &mainCamera);
//
//		//testObj.draw();
//		//sphereObject.draw();
//		//twoBalls.draw();
//
//		graphics.deviceCon->ClearDepthStencilView(graphics.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
//		mainWindow.rawMouseDelta = {};
//		graphics.swapChain->Present(0, 0);
//	}
//}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	/*
	RenderWindow window;

	Camera* camera = new Camera();
	window.setCamera(camera);

	Sphere* sphere = new Sphere();
	window.Draw(sphere);

	*/

	RenderWindow* renderWindow = new RenderWindow();
	Camera* mainCamera = new Camera(true);
	mainCamera->position = { 0, 3, -10 };
	renderWindow->setCamera(mainCamera);

	Sphere* sphere = new Sphere(renderWindow);
	Spherenic* spherenic = new Spherenic(renderWindow);

	ModeledObject* modeledObject = new ModeledObject(renderWindow->modelsContent->sphere);
	modeledObject->setPosition({0, 3, 0});

	ModeledObject* plane = new ModeledObject(renderWindow->modelsContent->plane);
	plane->setTexture(renderWindow->graphics->texturesContent->stoneWallAlbedo, 0);
	plane->setTexture(renderWindow->graphics->texturesContent->stoneWallNormalMap, 1);
	plane->setScale({1, 1, 1});

	PointLight whitePointLight = PointLight(renderWindow->graphics, (char*)"Models//sphere.obj", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->lightSourcePS);
	whitePointLight.setPosition(float3{ 0, 1, -3 });
	whitePointLight.setColor(float4{ 1, 1, 1, 1 });
	whitePointLight.setFactors(float3{ 1, 0.014f, 0.0007f });

	float k = 0;
	float timer = 0;

	renderWindow->graphics->setCameraToDraw(mainCamera);
	while (renderWindow->isOpen)
	{
		renderWindow->startDeltaTime();
		renderWindow->dispatchEvents();
		renderWindow->update();
		renderWindow->setBackRenderTargetAndDepthStencil();
		renderWindow->updatePointLights();
		renderWindow->clear(float4{ 0, 0, 0, 0 });

		timer += 1 * renderWindow->graphics->deltaTime;

		for (int i = 0; i < 1000; i++)
			renderWindow->Draw(plane);

		renderWindow->Draw(sphere);
		sphere->setPosition({k * 0.1f, 0, 3});
		sphere->setRotation({k * 0.1f, 0, 0});

		renderWindow->Draw(spherenic);
		spherenic->setRotation({k, 0, 0});
		spherenic->setPosition({ cos(k * 0.1f) * 7, 0, sin(k * 0.1f) * 7});

		k += 3.14f * renderWindow->graphics->deltaTime;
		whitePointLight.setPosition({cos(0.0f) * 2, 1, sin(0.0f) * 2});
		whitePointLight.draw(renderWindow->graphics, mainCamera);

		if ((int)timer % 2 == 1)
			modeledObject->setModel(renderWindow->modelsContent->plane);
		else
			modeledObject->setModel(renderWindow->modelsContent->sphere);

		renderWindow->Draw(modeledObject);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}