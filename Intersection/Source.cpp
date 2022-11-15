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
#include "BoxCollider.h"

#include <UI/ToggleGroupe.h>
#include <Font.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "text.h"
#include "InnerTexturesContent.h"
#include "UI/UIText.h"
#include "UI/Sprite.h"

void drawUI(RenderWindow* renderWindow, Camera* camer, UIText* fpsCounter)
{
	camer->setPerspectiveCoof(1);
	fpsCounter->text->setText("FPS: " + std::to_string(1 / renderWindow->graphics->deltaTime));
	renderWindow->Draw(fpsCounter, false, false);
	camer->setPerspectiveCoof(0);
}

void prepDraw(RenderWindow* renderWindow, ID3D11BlendState* blendState)
{
	renderWindow->graphics->deviceCon->OMSetBlendState(blendState, nullptr, 0xFFFFFFFFu);
	renderWindow->startDeltaTime();
	renderWindow->dispatchEvents();
	renderWindow->update();
	renderWindow->setBackRenderTargetAndDepthStencil();
	renderWindow->updatePointLights();
	renderWindow->clear(float4{ 0, 0, 0, 0 });
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow){
	RenderWindow* renderWindow = new RenderWindow();

	Camera* mainCamera = new Camera(renderWindow, true);
	mainCamera->position = { 0, 2, -2 };

	FT_Library* ftLibrary = new FT_Library();

	FT_Error error = FT_Init_FreeType(ftLibrary);
	if (error)
		throw;

	Font font = Font(renderWindow, ftLibrary, "fonts//Roboto-Regular.ttf");

	mainCamera->position = { 0, 0, -2 };
	mainCamera->moveSpeed = 3;

	TexturesContent::load(renderWindow);
	ShadersContent::load(renderWindow);
	ModelsContent::load(renderWindow);
	InnerModelsContent::load(renderWindow, ShadersContent::defaultVS, ShadersContent::defaultPS);
	InnerTexturesContent::load(renderWindow);
	UIElement::setStaticVertexAndPixelShaders(ShadersContent::defaultVS, ShadersContent::onlyTexturePS);

	StrategyCamera* strategyCamera = new StrategyCamera(renderWindow, { 0, 10, 0 }, { 3.14 / 3, 0, 0 });
	renderWindow->setCamera(mainCamera);
	World* world = new World(renderWindow, 1, 1);

	PointLight* pointLight1 = new PointLight(renderWindow, ModelsContent::sphere);
	//pointLight1->setPosition({-10, 0, -10 });
	pointLight1->setPosition({-10, 0, 0 });

	PointLight* pointLight2 = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight2->setPosition({ -10, 10, -10 });
	pointLight2->turn(false);

	PointLight* pointLight3 = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight3->setPosition({ 10, 10, -10 });
	pointLight3->turn(false);

	PointLight* pointLight4 = new PointLight(renderWindow, ModelsContent::sphere);
	pointLight4->setPosition({ 10, 0, -10 });
	pointLight4->turn(false);

	SkySphere* skySphere = new SkySphere(renderWindow, TexturesContent::textureSky);

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

	ModeledObject* sphere1 = new ModeledObject(renderWindow, ModelsContent::knight, 
		ShadersContent::defaultVS, 
		ShadersContent::PbrPS);
	sphere1->setScale({ 0.05f, 0.05f, 0.05f });
	sphere1->setTexture(TexturesContent::stoneWallAlbedo, 0);
	sphere1->setTexture(TexturesContent::flatNormalMap, 1);

	while (renderWindow->isOpen)
	{
		prepDraw(renderWindow, blendState);
		//renderWindow->Draw(skySphere, false);

		renderWindow->Draw(sphere1);

		renderWindow->Draw(pointLight1);
		//renderWindow->Draw(pointLight2);
		//renderWindow->Draw(pointLight3);
		//renderWindow->Draw(pointLight4);

		drawUI(renderWindow, mainCamera, fpsCounter);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}