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
#include "World.h"
#include "UI/UIElement.h"
#include "UI/Button.h"
#include "EventSwitchValue.h"
#include <UI/Toggle.h>
#include "Register.h"

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
	Register::init(renderWindow);

	Sphere* sphere = new Sphere(renderWindow);
	ModeledObject* plane = new ModeledObject(renderWindow, ModelsContent::plane);
	plane->setScale({100, 1, 100});

	//EntityTree* entityTree = new EntityTree(renderWindow);



	PointLight* pointLight = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 1, 1, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	bool pointLightTurnOn = true;
	EventSwitchValue<bool> switchingEvent = EventSwitchValue<bool>(&pointLightTurnOn, true, false);

	Button* testUIElement = new Button(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	testUIElement->color = { 0.18f, 0.18f, 0.18f };
	testUIElement->hoverColor = { 0.239f, 0.239f, 0.239f };
	testUIElement->pressColor = { 0.266f, 0.266f, 0.266f };
	testUIElement->addEvent(&switchingEvent);

	Toggle* toggle1 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle1->setSizeInPixels({ 20, 20 });
	toggle1->setPositionInPixels({20, 20});
	toggle1->color = { 0.18f, 0.18f, 0.18f };
	toggle1->hoverColor = { 0.239f, 0.239f, 0.239f };
	toggle1->pressColor = { 0.266f, 0.266f, 0.266f };

	Toggle* toggle2 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle2->setSizeInPixels({ 20, 20 });
	toggle2->setPositionInPixels({ 50, 20 });
	toggle2->color = { 0.18f, 0.18f, 0.18f };
	toggle2->hoverColor = { 0.239f, 0.239f, 0.239f };
	toggle2->pressColor = { 0.266f, 0.266f, 0.266f };

	Toggle* toggle3 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle3->setSizeInPixels({ 20, 20 });
	toggle3->setPositionInPixels({ 80, 20 });
	toggle3->color = { 0.18f, 0.18f, 0.18f };
	toggle3->hoverColor = { 0.239f, 0.239f, 0.239f };
	toggle3->pressColor = { 0.266f, 0.266f, 0.266f };

	SkySphere* skySphere = new SkySphere(renderWindow, TexturesContent::textureSky);

	World* world = new World(renderWindow, 100, 100, 1, 1);

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
		pointLight->turn(pointLightTurnOn);
		renderWindow->Draw(pointLight);
		renderWindow->Draw(plane);
		renderWindow->Draw(world);

		testUIElement->setSizeInPixels({ 200, 50 });
		renderWindow->Draw(testUIElement, false, false, false);
		renderWindow->Draw(toggle1, false, false, false);
		renderWindow->Draw(toggle2, false, false, false);
		renderWindow->Draw(toggle3, false, false, false);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}