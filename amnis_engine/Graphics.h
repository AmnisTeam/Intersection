#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <iostream>
#include <vector>
#include "RenderTarget.h"
#include "PointLight.h"
#include "decl.h"


class Camera;
class PointLight;
class VertexShader;
class PixelShader;
class Graphics
{
public:
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceCon;
	ID3D11RenderTargetView* backRenderTarget;
	RenderTarget* renderTarget;
	ID3D11Texture2D* depthStencilTexture;
	ID3D11DepthStencilView* depthStencilView;
	HWND hwnd;
	std::vector<PointLight*> pointLights2;
	int maxPointLightsCount = 500;
	ID3D11Buffer* pointLightsBuffer;
	ID3D11ShaderResourceView* pointLightsSRV;
	ID3D11Buffer* lightsCountsBuffer;
	VertexShader* defaultVS;
	PixelShader* defaultPS;
	PixelShader* lightPS;
	int resWidth;
	int resHeight;
	double deltaTime = 1 / 60.0;
	DECL Graphics();
	DECL void initDirectX11(HWND outputWindow, int backWidth = -1, int backHeight = -1);
	DECL void initDepthStencil();
	DECL void setFirstOldClockAndDeltaTime();
	DECL void updateDeltaTime();
	DECL void updatePointLights();
private:
	long long oldClock;
};

