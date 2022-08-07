#include "MainWindow.h"
#include "Graphics.h"
#include "DirectLightSource.h"
#include "Model.h"
#include "Camera.h"
#include "DirectLightSource.h"
#include "PointLight.h"
#include "Sphere.h"
#include <chrono>
#include "Spherenic.h"
#include "ModeledObject.h"
#include "SkySphere.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	RenderWindow* renderWindow = new RenderWindow();
	Camera* mainCamera = new Camera(true);
	mainCamera->position = { 0, 3, -10 };
	renderWindow->setCamera(mainCamera);

	Sphere* sphere = new Sphere(renderWindow);

	ModeledObject* tree = new ModeledObject(renderWindow, renderWindow->modelsContent->tree);
	tree->setTexture(renderWindow->graphics->texturesContent->flatNormalMap, 1);
	////tree->setTexture(renderWindow->graphics->texturesContent->ghosthzAlbedo, 0);
	tree->setRotation({-3.14 / 2, 0, 0});
	tree->setScale({1, 1, 1});

	PointLight* pointLight = new PointLight(renderWindow, renderWindow->modelsContent->sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 1, 1, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	SkySphere* skySphere = new SkySphere(renderWindow, renderWindow->graphics->texturesContent->textureSky);

	while (renderWindow->isOpen)
	{
		renderWindow->startDeltaTime();
		renderWindow->dispatchEvents();
		renderWindow->update();
		renderWindow->setBackRenderTargetAndDepthStencil();
		renderWindow->updatePointLights();
		renderWindow->clear(float4{ 0, 0, 0, 0 });

		renderWindow->Draw(skySphere, false);
		renderWindow->Draw(sphere);
		renderWindow->Draw(pointLight);
		renderWindow->Draw(tree);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}