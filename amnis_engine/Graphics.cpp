#include "pch.h"
#include "Graphics.h"
#include "PointLight.h"

Graphics::Graphics()
{

}

void Graphics::initDirectX11(HWND outputWindow, int backWidth, int backHeight)
{
    hwnd = outputWindow;
    RECT clientRect;
    GetClientRect(outputWindow, &clientRect);
    if (backWidth == -1 || backHeight == -1)
    {
        backWidth = clientRect.right;
        backHeight = clientRect.bottom;
    }
    resWidth = backWidth;
    resHeight = backHeight;

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //swapChainDesc.BufferDesc.Width = backWidth;
    //swapChainDesc.BufferDesc.Height = backHeight;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = outputWindow;
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, NULL, &deviceCon);
    if (FAILED(hr))throw;

    ID3D11Texture2D* backBuffer;
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
    if (FAILED(hr))throw;

    renderTarget = new RenderTarget();

    //hr = device->CreateRenderTargetView(backBuffer, NULL, &backRenderTarget);
    hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTarget->renderTarget);
    if (FAILED(hr)) throw;

    backRenderTarget = renderTarget->renderTarget;

    D3D11_VIEWPORT viewPort{};
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.Width = clientRect.right;
    viewPort.Height = clientRect.bottom;
    deviceCon->RSSetViewports(1, &viewPort);

    shadersContent = new ShadersContent(this);

    D3D11_BUFFER_DESC pointLightsBufferDesc{};
    pointLightsBufferDesc.ByteWidth = sizeof(PointLight::PointLightDesc) * maxPointLightsCount;
    pointLightsBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Here may be an error
    pointLightsBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    pointLightsBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    pointLightsBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    pointLightsBufferDesc.StructureByteStride = sizeof(PointLight::PointLightDesc);

    hr = device->CreateBuffer(&pointLightsBufferDesc, NULL, &pointLightsBuffer);
    if (FAILED(hr)) throw;

    D3D11_SHADER_RESOURCE_VIEW_DESC pointLightsSRVDesc{};
    pointLightsSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
    pointLightsSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    pointLightsSRVDesc.Buffer.FirstElement = 0;
    pointLightsSRVDesc.Buffer.NumElements = maxPointLightsCount;

    hr = device->CreateShaderResourceView(pointLightsBuffer, &pointLightsSRVDesc, &pointLightsSRV);
    if (FAILED(hr)) throw;

    D3D11_BUFFER_DESC lightsCountsBufferDesc{};
    lightsCountsBufferDesc.ByteWidth = sizeof(unsigned int) * 4;
    lightsCountsBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    lightsCountsBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightsCountsBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    lightsCountsBufferDesc.MiscFlags = 0;
    lightsCountsBufferDesc.StructureByteStride = 0;

    hr = device->CreateBuffer(&lightsCountsBufferDesc, NULL, &lightsCountsBuffer);
    if (FAILED(hr)) throw;
}

void Graphics::initDepthStencil()
{
    D3D11_TEXTURE2D_DESC depthStencilTextureDesc{};
    depthStencilTextureDesc.Width = resWidth;
    depthStencilTextureDesc.Height = resHeight;
    depthStencilTextureDesc. MipLevels = 1;
    depthStencilTextureDesc.ArraySize = 1;
    depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilTextureDesc.SampleDesc.Count = 1;
    depthStencilTextureDesc.SampleDesc.Quality = 0;
    depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilTextureDesc.CPUAccessFlags = 0;
    depthStencilTextureDesc.MiscFlags = 0;

    device->CreateTexture2D(&depthStencilTextureDesc, NULL, &depthStencilTexture);
    device->CreateDepthStencilView(depthStencilTexture, NULL, &depthStencilView);
    oldClock = clock();
}

void Graphics::initTexturesContent()
{
    texturesContent = new TexturesContent(this);
}

void Graphics::setFirstOldClockAndDeltaTime()
{
    oldClock = clock();
    deltaTime = 1.0 / 60.0;
}

void Graphics::updateDeltaTime()
{
    double check = clock() - oldClock;
    deltaTime = max((double)(clock() - oldClock) / 1000.0, 0.000001);
    oldClock = clock();
}

void Graphics::updatePointLights()
{
    //D3D11_MAPPED_SUBRESOURCE mappedSubResource{};
    //HRESULT hr = deviceCon->Map(pointLightsBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubResource);
    //if (FAILED(hr)) throw;

    //unsigned int offset = 0;
    //for (int i = 0; (i < pointLights.size()) && (i < maxPointLightsCount); i++)
    //{
    //    PointLight::PointLightDesc pointLightDesc{};
    //    pointLightDesc.color = pointLights[i]->color;
    //    pointLightDesc.kc = pointLights[i]->kc;
    //    pointLightDesc.kl = pointLights[i]->kl;
    //    pointLightDesc.kq = pointLights[i]->kq;
    //    pointLightDesc.position = pointLights[i]->getPosition();
    //    pointLightDesc.turnedOn = pointLights[i]->turnedOn;

    //    memcpy((char*)mappedSubResource.pData + offset, &pointLightDesc, sizeof(PointLight::PointLightDesc));
    //    offset += sizeof(PointLight::PointLightDesc);
    //}

    //deviceCon->Unmap(pointLightsBuffer, NULL);

    //hr = deviceCon->Map(lightsCountsBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubResource);
    //if (FAILED(hr)) throw;

    //unsigned int count = pointLights.size();
    //memcpy((char*)mappedSubResource.pData, &count, sizeof(PointLight::PointLightDesc));

    //deviceCon->Unmap(lightsCountsBuffer, NULL);

    D3D11_MAPPED_SUBRESOURCE mappedSubResource{};
    HRESULT hr = deviceCon->Map(pointLightsBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubResource);
    if (FAILED(hr)) throw;

    unsigned int offset = 0;
    for (int i = 0; (i < pointLights2.size()) && (i < maxPointLightsCount); i++)
    {
        PointLight::PointLightDesc pointLightDesc{};
        pointLightDesc.color = pointLights2[i]->color;
        pointLightDesc.kc = pointLights2[i]->kc;
        pointLightDesc.kl = pointLights2[i]->kl;
        pointLightDesc.kq = pointLights2[i]->kq;
        pointLightDesc.position = pointLights2[i]->getPosition();
        pointLightDesc.turnedOn = pointLights2[i]->turnedOn;

        memcpy((char*)mappedSubResource.pData + offset, &pointLightDesc, sizeof(PointLight::PointLightDesc));
        offset += sizeof(PointLight::PointLightDesc);
    }

    deviceCon->Unmap(pointLightsBuffer, NULL);

    hr = deviceCon->Map(lightsCountsBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubResource);
    if (FAILED(hr)) throw;

    unsigned int count = pointLights2.size();
    memcpy((char*)mappedSubResource.pData, &count, sizeof(PointLight::PointLightDesc));

    deviceCon->Unmap(lightsCountsBuffer, NULL);
}