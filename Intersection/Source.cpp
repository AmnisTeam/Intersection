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
#include <UI/ToggleGroupe.h>


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

	PointLight* pointLight = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 0, 0, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	PointLight* pointLight1 = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight1->setPosition(float3{ -5, 1, -3 });
	pointLight1->setColor(float4{ 0, 1, 0, 1 });
	pointLight1->setFactors(float3{ 1, 0.014f, 0.0007f });

	PointLight* pointLight2 = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight2->setPosition(float3{ 5, 1, -3 });
	pointLight2->setColor(float4{ 0, 0, 1, 1 });
	pointLight2->setFactors(float3{ 1, 0.014f, 0.0007f });


	UIStyle style{};
	style.color = { 0.18f, 0.18f, 0.18f };
	style.hoverColor = { 0.239f, 0.239f, 0.239f };
	style.pressColor = { 0.266f, 0.266f, 0.266f };
	style.onColor = mymath::getColor({ 9, 222, 154, 255 });
	style.onHoverColor = mymath::getColor({ 35, 248, 180, 255 });
	style.onPressColor = mymath::getColor({ 72, 255, 217, 255 });

	bool pointLightTurnOn = true;
	EventSwitchValue<bool> switchingEvent = EventSwitchValue<bool>(&pointLightTurnOn, true, false);

	Button* button = new Button(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	button->setStyle(style);
	button->addEvent(&switchingEvent);

	Toggle* toggle1 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle1->setSizeInPixels({ 20, 20 });
	toggle1->setPositionInPixels({20, 20});
	toggle1->setStyle(style);

	Toggle* toggle2 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle2->setSizeInPixels({ 20, 20 });
	toggle2->setPositionInPixels({ 50, 20 });
	toggle2->setStyle(style);

	Toggle* toggle3 = new Toggle(renderWindow, ShadersContent::defaultVS, ShadersContent::onlyTexturePS);
	toggle3->setSizeInPixels({ 20, 20 });
	toggle3->setPositionInPixels({ 80, 20 });
	toggle3->setStyle(style);

	ToggleGroupe* toggleGroupe = new ToggleGroupe(renderWindow);
	toggleGroupe->add(toggle1);
	toggleGroupe->add(toggle2);
	toggleGroupe->add(toggle3);

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

		toggleGroupe->update();

		renderWindow->Draw(skySphere, false);
		renderWindow->Draw(sphere);
		pointLight->turn(toggle2->getState());
		pointLight1->turn(toggle1->getState());
		pointLight2->turn(toggle3->getState());
		renderWindow->Draw(pointLight);
		renderWindow->Draw(pointLight1);
		renderWindow->Draw(pointLight2);
		renderWindow->Draw(plane);
		renderWindow->Draw(world);

		button->setSizeInPixels({ 200, 50 });
		renderWindow->Draw(button, false, false, false);
		renderWindow->Draw(toggle1, false, false, false);
		renderWindow->Draw(toggle2, false, false, false);
		renderWindow->Draw(toggle3, false, false, false);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}