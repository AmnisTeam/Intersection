#include "pch.h"
#include "RenderWindow.h"
#include "Camera.h"

RenderWindow::RenderWindow()
{
	window = new MainWindow();
	window->create(L"Window");
	graphics = new Graphics();
	graphics->initDirectX11(window->hwnd);
	graphics->initDepthStencil();
	ShowWindow(window->hwnd, 1);
	graphics->initTexturesContent();
	modelsContent = new ModelsContent(this);

	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = nullptr;

	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		throw;

	msg = {};

	//RAWINPUTDEVICE rid{};
	//rid.usUsagePage = 0x01;
	//rid.usUsage = 0x02;
	//rid.dwFlags = 0;
	//rid.hwndTarget = nullptr;

	//if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
	//	throw;
}

RenderWindow::~RenderWindow()
{
	delete window;
	delete graphics;
	delete modelsContent;
}

//void RenderWindow::showWindow()
//{
//}

void RenderWindow::Draw(IDrawable* object, bool depthStencilOn)
{
	RenderState renderState = RenderState(this);
	renderState.modelMatrix = DirectX::XMMatrixIdentity();
	renderState.depthStencilOn = depthStencilOn;
	object->draw(graphics->renderTarget, renderState);
}

void RenderWindow::display()
{
	graphics->deviceCon->ClearDepthStencilView(graphics->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	window->rawMouseDelta = {};
	graphics->swapChain->Present(0, 0);
}

void RenderWindow::update()
{
	boundCamera->responseInput(graphics, window);
	boundCamera->update(graphics);
}

void RenderWindow::dispatchEvents()
{
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			isOpen = false;
	}
}

void RenderWindow::clear(float4 color)
{
	graphics->deviceCon->ClearRenderTargetView(graphics->renderTarget->renderTarget, (const FLOAT*)&color);
}

void RenderWindow::updatePointLights()
{
	graphics->deviceCon->PSSetShaderResources(9, 1, &graphics->pointLightsSRV);
	graphics->deviceCon->PSSetConstantBuffers(9, 1, &graphics->lightsCountsBuffer);
}

void RenderWindow::setCamera(Camera* camera)
{
	boundCamera = camera;
}

void RenderWindow::startDeltaTime()
{
	start = std::chrono::steady_clock::now();
}

void RenderWindow::endDeltaTime()
{
	auto end = std::chrono::steady_clock::now();
	long long elapsedTimeNano = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	graphics->deltaTime = elapsedTimeNano * 0.000000001;
}

void RenderWindow::setBackRenderTargetAndDepthStencil()
{
	graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
}
