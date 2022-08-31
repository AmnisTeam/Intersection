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
#include <Font.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "text.h"
#include "InnerTexturesContent.h"
#include "UI/UIText.h"
#include "UI/Sprite.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow){
	RenderWindow* renderWindow = new RenderWindow();

	TexturesContent::load(renderWindow);
	ModelsContent::load(renderWindow);
	ShadersContent::load(renderWindow);
	InnerModelsContent::load(renderWindow, ShadersContent::defaultVS, ShadersContent::defaultPS);
	InnerTexturesContent::load(renderWindow);
	UIElement::setStaticVertexAndPixelShaders(ShadersContent::defaultVS, ShadersContent::UIElementPS);
	//UIElement::setStaticVertexAndPixelShaders(ShadersContent::defaultVS, ShadersContent::onlyTexturePS);


	Camera* mainCamera = new Camera(renderWindow, true);
	mainCamera->position = { 0, 2, -2 };
	renderWindow->setCamera(mainCamera);

	StrategyCamera* strategyCamera = new StrategyCamera(renderWindow, { 0, 10, 0 }, { 3.14 / 3, 0, 0 });
	//renderWindow->setCamera(strategyCamera);


	FT_Library* ftLibrary = new FT_Library();

	FT_Error error = FT_Init_FreeType(ftLibrary);
	if (error)
		throw;

	Font font = Font(renderWindow, ftLibrary, "fonts//Roboto-Regular.ttf");

	Sphere* sphere = new Sphere(renderWindow);
	sphere->setPosition(float3{ 0, 0, 1 });
	ModeledObject* plane = new ModeledObject(renderWindow, ModelsContent::plane);
	plane->setTexture(TexturesContent::stoneWallAlbedo, 0);
	plane->setTexture(TexturesContent::stoneWallNormalMap, 1);
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
	//checkbox3->setSprite(TexturesContent::textureSky, float4{0, 0, 1, 1});

	ToggleGroupe* toggleGroupe = new ToggleGroupe(renderWindow);
	toggleGroupe->add(toggle1);
	toggleGroupe->add(toggle2);
	toggleGroupe->add(toggle3);

	Toggle* fontAtlas = new Toggle(renderWindow, { 0, 0 }, toggleSize, whiteLightsStyle);
	fontAtlas->overlayColor = { 1, 1, 1, 1 };
	fontAtlas->hoverColor = { 1, 1, 1, 1 };
	fontAtlas->pressColor = { 1, 1, 1, 1 };
	fontAtlas->onColor = { 1, 1, 1, 1 };
	fontAtlas->onHoverColor = { 1, 1, 1, 1 };
	fontAtlas->onPressColor = { 1, 1, 1, 1 };
	fontAtlas->setPivot({ 0, 0 });
	fontAtlas->setSizeInPixels(float2{ (float)font.texture->width, (float)font.texture->height});

	SkySphere* skySphere = new SkySphere(renderWindow, TexturesContent::textureSky);

	World* world = new World(renderWindow, 100, 100, 1, 1);

	PointLight* mousePointLight = new PointLight(renderWindow, ModelsContent::sphere, { 20, 5, 0 }, { 1, 1, 1, 1 });

	ID3D11BlendState* blendState;
	D3D11_BLEND_DESC blendDesc{};
	auto &brt = blendDesc.RenderTarget[0];

	brt.BlendEnable = true;
	brt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	brt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	brt.BlendOp = D3D11_BLEND_OP_ADD;
	brt.SrcBlendAlpha = D3D11_BLEND_ZERO;
	brt.DestBlendAlpha = D3D11_BLEND_ZERO;
	brt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	brt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = renderWindow->graphics->device->CreateBlendState(&blendDesc, &blendState);
	if (FAILED(hr)) throw;

	UIText* fpsCounter = new UIText(renderWindow, 256, ShadersContent::defaultVS, ShadersContent::TextPS);
	fpsCounter->text->setFont(&font);
	fpsCounter->text->setFontSize(13);
	fpsCounter->text->setAttachment(float2{ 0, 0.5f });
	fpsCounter->text->setTextOrigin(float2{ 0.1f, -0.2f });
	fpsCounter->setSizeInPixels(float2{ 400, 30 });
	fpsCounter->setPositionInPixels(float2{ 0, 6 });
	fpsCounter->setAnchor({ 0, 0 });
	fpsCounter->setPivot({ 0, 0 });

	UIText* positionInfo = new UIText(renderWindow, 256, ShadersContent::defaultVS, ShadersContent::TextPS);
	positionInfo->text->setFont(&font);
	positionInfo->text->setFontSize(13);
	positionInfo->text->setAttachment(float2{0, 0.5f});
	positionInfo->text->setTextOrigin(float2{0.1f, -0.2f});
	positionInfo->setSizeInPixels(float2{400, 30});
	positionInfo->setPositionInPixels(float2{0, 26});
	positionInfo->setAnchor({ 0, 0 });
	positionInfo->setPivot({ 0, 0 });
	positionInfo->overlayColor = { 0, 1, 1, 1 };
	positionInfo->text->setColor(float4{ 1, 0, 0, 1 });

	Text* text = new Text(renderWindow, 256, ShadersContent::defaultVS, ShadersContent::TextPS);
	text->setFont(&font);
	text->setText("Hello world!");
	text->setStringsGap(0.5f);
	text->setAttachment(float2{0.5f, 0.5f});
	text->setColor(float4{1, 0, 0, 1});

	Sprite* testSpirte = new Sprite(renderWindow, TexturesContent::bugAlbedo, float4{ 0.45f, 0.45f, 0.55f, 0.55f }, ShadersContent::defaultVS, ShadersContent::UIElementPS);
	testSpirte->overlayColor = {1, 0, 0, 1};
	testSpirte->shadeColor = {0, 0, 1, 1};
	testSpirte->setShade(0);
	testSpirte->setOverlay(0);

	//Toggle* testSquare = new Toggle(renderWindow, { toggleSize.x + toggleOffset.x, -toggleOffset.y }, toggleSize, style);
	//testSquare->setAnchor(positionInfo->getAnchor());
	//testSquare->setPivot(positionInfo->getPivot());
	//testSquare->setSizeInPixels(positionInfo->getSizeInPixels());
	//testSquare->setPositionInPixels(positionInfo->getPositionInPixels());

	float a = 0;
	while (renderWindow->isOpen)
	{
		a += 1 * renderWindow->graphics->deltaTime;
		renderWindow->graphics->deviceCon->OMSetBlendState(blendState, nullptr, 0xFFFFFFFFu);

		renderWindow->startDeltaTime();
		renderWindow->dispatchEvents();
		renderWindow->update();
		renderWindow->setBackRenderTargetAndDepthStencil();
		renderWindow->updatePointLights();
		renderWindow->clear(float4{ 0, 0, 0, 0 });

		toggleGroupe->update();


		renderWindow->Draw(skySphere, false);
		//renderWindow->Draw(sphere);


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
		//renderWindow->Draw(world);
		font.texture->bind(0);
		RECT clientRect;
		GetClientRect(renderWindow->window->hwnd, &clientRect);
		float width = clientRect.right;
		float height = clientRect.bottom;
		float angle = renderWindow->boundCamera->angle;
		float nearPlane = angle;
		float aspect = renderWindow->boundCamera->aspect;

		float3 normalizedMousePosition = float3
		{
		((renderWindow->window->mousePos.x / width) * 2 - 1) / aspect,
		-((renderWindow->window->mousePos.y / height) * 2 - 1),
		nearPlane
		};

		float3 spacedNormalizedMousePosition = renderWindow->boundCamera->position + renderWindow->boundCamera->bitangent * normalizedMousePosition.x + renderWindow->boundCamera->normal * normalizedMousePosition.y + renderWindow->boundCamera->tangent * normalizedMousePosition.z;

		float3 direction = mymath::normalize(spacedNormalizedMousePosition - renderWindow->boundCamera->position);

		mousePointLight->setPosition(renderWindow->boundCamera->position + direction * 3);
		renderWindow->Draw(mousePointLight);
		renderWindow->Draw(text);
		mainCamera->setPerspectiveCoof(1);


		//testSquare->setAnchor(positionInfo->getAnchor());
		//testSquare->setPivot(positionInfo->getPivot());
		//testSquare->setSizeInPixels(positionInfo->getSizeInPixels());
		//renderWindow->Draw(testSquare, false, false);

		fpsCounter->text->setText("FPS: " + std::to_string(1 / renderWindow->graphics->deltaTime));
		renderWindow->Draw(fpsCounter, false, false);

		positionInfo->text->setText("Position: "
			+ std::to_string(renderWindow->boundCamera->position.x) + " "
			+ std::to_string(renderWindow->boundCamera->position.y) + " "
			+ std::to_string(renderWindow->boundCamera->position.z)
		);

		renderWindow->Draw(positionInfo, false, false);
		renderWindow->Draw(button, false, false);
		renderWindow->Draw(toggle1, false, false);
		renderWindow->Draw(toggle2, false, false);
		renderWindow->Draw(toggle3, false, false);

		renderWindow->Draw(checkbox1, false, false);
		renderWindow->Draw(checkbox2, false, false);
		renderWindow->Draw(checkbox3, false, false);
		renderWindow->Draw(testSpirte, false, false);
		mainCamera->setPerspectiveCoof(0);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}