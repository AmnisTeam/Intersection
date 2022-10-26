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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow){
	RenderWindow* renderWindow = new RenderWindow();

	Camera* mainCamera = new Camera(renderWindow, true);
	mainCamera->position = { 0, 2, -2 };

	FT_Library* ftLibrary = new FT_Library();

	FT_Error error = FT_Init_FreeType(ftLibrary);
	if (error)
		throw;

	Font font = Font(renderWindow, ftLibrary, "fonts//Roboto-Regular.ttf");

	mainCamera->position = { 0, 0, 0 };

	TexturesContent::load(renderWindow);
	ShadersContent::load(renderWindow);
	ModelsContent::load(renderWindow);
	InnerModelsContent::load(renderWindow, ShadersContent::defaultVS, ShadersContent::defaultPS);
	InnerTexturesContent::load(renderWindow);
	UIElement::setStaticVertexAndPixelShaders(ShadersContent::defaultVS, ShadersContent::onlyTexturePS);

	StrategyCamera* strategyCamera = new StrategyCamera(renderWindow, { 0, 10, 0 }, { 3.14 / 3, 0, 0 });
	renderWindow->setCamera(strategyCamera);
	World* world = new World(renderWindow, 1, 1);

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

	UIText* positionInfo = new UIText(renderWindow, 256, ShadersContent::defaultVS, ShadersContent::TextPS);
	positionInfo->text->setFont(&font);
	positionInfo->text->setFontSize(13);
	positionInfo->text->setAttachment(float2{0, 0.5f});
	positionInfo->text->setTextOrigin(float2{0.1f, -0.2f});
	positionInfo->setSizeInPixels(float2{400, 30});
	positionInfo->setPositionInPixels(float2{0, 26});
	positionInfo->setAnchor({ 0, 0 });
	positionInfo->setPivot({ 0, 0 });

	Text* text = new Text(renderWindow, 256, ShadersContent::defaultVS, ShadersContent::TextPS);
	text->setFont(&font);
	text->setText("Hello world!");
	text->setStringsGap(0.5f);
	text->setAttachment(float2{0.5f, 0.5f});


	Sprite* testSpirte = new Sprite(renderWindow, TexturesContent::bugAlbedo, float4{ 0.45f, 0.45f, 0.55f, 0.55f }, ShadersContent::defaultVS, ShadersContent::UIElementPS);
	testSpirte->overlayColor = {1, 0, 0, 1};
	testSpirte->shadeColor = {0, 0, 1, 1};
	testSpirte->setAnchor(float2{1, 0});
	testSpirte->setPivot(float2{1, 0});
	testSpirte->setShade(0);
	testSpirte->setOverlay(0);

	ModeledObject* bug = new ModeledObject(renderWindow, ModelsContent::bug);
	bug->setPosition({-5, 0, 0});

	while (renderWindow->isOpen)
	{
		renderWindow->graphics->deviceCon->OMSetBlendState(blendState, nullptr, 0xFFFFFFFFu);

		renderWindow->startDeltaTime();
		renderWindow->dispatchEvents();
		renderWindow->update();
		renderWindow->setBackRenderTargetAndDepthStencil();
		renderWindow->updatePointLights();
		renderWindow->clear(float4{ 0, 0, 0, 0 });

		renderWindow->Draw(skySphere, false);

		world->update();
		font.texture->bind(0);

		renderWindow->Draw(world);

		renderWindow->Draw(text);
		mainCamera->setPerspectiveCoof(1);

		fpsCounter->text->setText("FPS: " + std::to_string(1 / renderWindow->graphics->deltaTime));
		renderWindow->Draw(fpsCounter, false, false);

		positionInfo->text->setText("Position: "
			+ std::to_string(renderWindow->boundCamera->position.x) + " "
			+ std::to_string(renderWindow->boundCamera->position.y) + " "
			+ std::to_string(renderWindow->boundCamera->position.z)
		);

		renderWindow->Draw(positionInfo, false, false);

		mainCamera->setPerspectiveCoof(0);
		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}