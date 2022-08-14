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
//#include <SpriteBatch.h>
//#include <SpriteFont.h>
#include <ft2build.h>
#include FT_FREETYPE_H

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	RenderWindow* renderWindow = new RenderWindow();
	Camera* mainCamera = new Camera(true);

	FT_Library  library;
	FT_Face     face;

	FT_Error error = FT_Init_FreeType(&library);
	if (error)
		throw;

	error = FT_New_Face(library, "fonts\\Lato-ThinItalic.ttf", 0, &face);
	if (error == FT_Err_Unknown_File_Format)
		throw;
	else if (error)
		throw;

	FT_UInt glyph_index = FT_Get_Char_Index(face, 'a');
	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error)
		throw;

	if(face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	face->glyph->bitmap;



	//DirectX::SpriteBatch* spriteBatch = new DirectX::SpriteBatch(renderWindow->graphics->deviceCon);
	//DirectX::SpriteFont* spriteFont = new DirectX::SpriteFont(renderWindow->graphics->device, L"fonts//Lato-ThinItalic.ttf");


	//mainCamera->position = { 0, 3, -10 };
	mainCamera->position = { 0, 0, 0 };
	renderWindow->setCamera(mainCamera);

	StrategyCamera* strategyCamera = new StrategyCamera({ 0, 10, 0 }, { 3.14 / 3, 0, 0 });
	renderWindow->setCamera(strategyCamera);

	TexturesContent::load(renderWindow);
	ModelsContent::load(renderWindow);
	ShadersContent::load(renderWindow);
	UIElement::setStaticVertexAndPixelShaders(ShadersContent::defaultVS, ShadersContent::onlyTexturePS);

	Sphere* sphere = new Sphere(renderWindow);
	ModeledObject* plane = new ModeledObject(renderWindow, ModelsContent::plane);
	plane->setScale({100, 1, 100});

	//EntityTree* entityTree = new EntityTree(renderWindow);

	PointLight* pointLight = new PointLight(renderWindow, ModelsContent::sphere, { -5, 1, -3 }, { 1, 0, 0, 1 });
	PointLight* pointLight1 = new PointLight(renderWindow, ModelsContent::sphere, { 0, 1, -3 }, { 0, 1, 0, 1 });
	PointLight* pointLight2 = new PointLight(renderWindow, ModelsContent::sphere, { 5, 1, -3 }, { 0, 0, 1, 1 });

	PointLight* pointLight3 = new PointLight(renderWindow, ModelsContent::sphere, { -20, 5, 0 }, { 1, 1, 1, 1 });
	PointLight* pointLight4 = new PointLight(renderWindow, ModelsContent::sphere, { 0, 5, 20 }, { 1, 1, 1, 1 });
	PointLight* pointLight5 = new PointLight(renderWindow, ModelsContent::sphere, { 20, 5, 0 }, { 1, 1, 1, 1 });

	UIStyle style{};
	style.color = { 0.18f, 0.18f, 0.18f };
	style.hoverColor = { 0.239f, 0.239f, 0.239f };
	style.pressColor = { 0.266f, 0.266f, 0.266f };
	style.onColor = mymath::getColor({ 9, 222, 154, 255 });
	style.onHoverColor = mymath::getColor({ 35, 248, 180, 255 });
	style.onPressColor = mymath::getColor({ 72, 255, 217, 255 });

	UIStyle whiteLightsStyle{};
	whiteLightsStyle.color = { 0.18f, 0.18f, 0.18f };
	whiteLightsStyle.hoverColor = { 0.239f, 0.239f, 0.239f };
	whiteLightsStyle.pressColor = { 0.266f, 0.266f, 0.266f };
	whiteLightsStyle.onColor = mymath::getColor({ 228, 228, 288, 255 });
	whiteLightsStyle.onHoverColor = mymath::getColor({ 240, 240, 240, 255 });
	whiteLightsStyle.onPressColor = mymath::getColor({ 255, 255, 255, 255 });

	bool pointLightTurnOn = true;
	EventSwitchValue<bool> switchingEvent = EventSwitchValue<bool>(&pointLightTurnOn, true, false);

	Button* button = new Button(renderWindow, { 20 , -20 }, { 200, 200}, style);
	button->addEvent(&switchingEvent);
	button->setPivot({0.0f, 1.0f});
	button->setAnchor({ 0.0f , 1.0f });

	float2 toggleSize = {50, 50};
	float2 toggleOffset = {20, 20};

	Toggle* toggle1 = new Toggle(renderWindow, { -toggleSize.x - toggleOffset.x, -toggleOffset.x }, toggleSize, style);
	toggle1->setAnchor({ 0.5f, 1 });
	toggle1->setPivot({ 0.5f, 1 });
	toggle1->onColor = mymath::getColor({ 195, 0, 0, 255 });
	toggle1->onHoverColor = mymath::getColor({ 225, 0, 0, 255 });
	toggle1->onPressColor = mymath::getColor({ 255, 0, 0, 255 });



	Toggle* toggle2 = new Toggle(renderWindow, { 0, -toggleOffset.y }, toggleSize, style);
	toggle2->setAnchor({ 0.5f, 1 });
	toggle2->setPivot({ 0.5f, 1 });
	toggle2->onColor = mymath::getColor({ 0, 195, 0, 255 });
	toggle2->onHoverColor = mymath::getColor({ 0, 225, 0, 255 });
	toggle2->onPressColor = mymath::getColor({ 0, 255, 0, 255 });



	Toggle* toggle3 = new Toggle(renderWindow, { toggleSize.x + toggleOffset.x, -toggleOffset.y }, toggleSize, style);
	toggle3->setAnchor({ 0.5f, 1 });
	toggle3->setPivot({ 0.5f, 1 });
	toggle3->onColor = mymath::getColor({ 0, 0, 195, 255 });
	toggle3->onHoverColor = mymath::getColor({ 0, 0, 225, 255 });
	toggle3->onPressColor = mymath::getColor({ 0, 0, 255, 255 });

	Toggle* checkbox1 = new Toggle(renderWindow, { -toggleSize.x - toggleOffset.x, -toggleSize.y - toggleOffset.y * 2 }, toggleSize, whiteLightsStyle);
	checkbox1->setAnchor({ 0.5f, 1 });
	checkbox1->setPivot({ 0.5f, 1 });
	Toggle* checkbox2 = new Toggle(renderWindow, { 0, -toggleSize.y - toggleOffset.y * 2 }, toggleSize, whiteLightsStyle);
	checkbox2->setAnchor({ 0.5f, 1 });
	checkbox2->setPivot({ 0.5f, 1 });
	Toggle* checkbox3 = new Toggle(renderWindow, { toggleSize.x + toggleOffset.x, - toggleSize.y -toggleOffset.y * 2 }, toggleSize, whiteLightsStyle);
	checkbox3->setAnchor({ 0.5f, 1 });
	checkbox3->setPivot({ 0.5f, 1 });

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

		pointLight->turn(toggle1->getState());
		pointLight1->turn(toggle2->getState());
		pointLight2->turn(toggle3->getState());

		renderWindow->Draw(pointLight);
		renderWindow->Draw(pointLight1);
		renderWindow->Draw(pointLight2);

		pointLight3->turn(checkbox1->getState());
		pointLight4->turn(checkbox2->getState());
		pointLight5->turn(checkbox3->getState());
		renderWindow->Draw(pointLight3);
		renderWindow->Draw(pointLight4);
		renderWindow->Draw(pointLight5);

		renderWindow->Draw(plane);
		renderWindow->Draw(world);

		renderWindow->Draw(button, false, false, false);
		renderWindow->Draw(toggle1, false, false, false);
		renderWindow->Draw(toggle2, false, false, false);
		renderWindow->Draw(toggle3, false, false, false);

		renderWindow->Draw(checkbox1, false, false, false);
		renderWindow->Draw(checkbox2, false, false, false);
		renderWindow->Draw(checkbox3, false, false, false);



		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}