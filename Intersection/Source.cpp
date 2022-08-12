#include "MainWindow.h"
#include "Graphics.h"
#include "Model.h"
#include "PointLight.h"
#include "Sphere.h"
#include <chrono>
#include "Spherenic.h"
#include "ModeledObject.h"
#include "SkySphere.h"
#include "entities/EntityTree.h"
#include "ModelsContent.h"
#include "TexturesContent.h"
#include "ShadersContent.h"
#include "StrategyCamera.h"
#include "UI/UIElement.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	RenderWindow* renderWindow = new RenderWindow();
	Camera* mainCamera = new Camera(true);
	//mainCamera->position = { 0, 3, -10 };
	mainCamera->position = { 0, 0, 0 };
	renderWindow->setCamera(mainCamera);

	StrategyCamera* strategyCamera = new StrategyCamera({ 0, 10, 0 }, { 3.14 / 3, 0, 0 });
	renderWindow->setCamera(strategyCamera);

	TexturesContent::load(renderWindow);
	ModelsContent::load(renderWindow);
	ShadersContent::load(renderWindow);

	Sphere* sphere = new Sphere(renderWindow);
	ModeledObject* plane = new ModeledObject(renderWindow, ModelsContent::plane);
	plane->setScale({100, 1, 100});

	//EntityTree* entityTree = new EntityTree(renderWindow);

	UIElement* testUIElement = new UIElement(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	testUIElement->setPosition({0, 0, 1});
	testUIElement->setScale({0.5f, 0.5f, 1});

	PointLight* pointLight = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 1, 1, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	SkySphere* skySphere = new SkySphere(renderWindow, TexturesContent::textureSky);
	float a = 0;
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
		renderWindow->Draw(plane);
		//renderWindow->Draw(entityTree);
		//renderWindow->Draw(tree);
		renderWindow->Draw(testUIElement, false, false, false);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}