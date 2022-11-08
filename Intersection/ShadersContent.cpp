#include "pch.h"
#include "ShadersContent.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RenderWindow.h"

VertexShader* ShadersContent::defaultVS;
PixelShader* ShadersContent::defaultPS;
PixelShader* ShadersContent::lightSourcePS;
PixelShader* ShadersContent::skyPS;
PixelShader* ShadersContent::onlyTexturePS;
PixelShader* ShadersContent::TextPS;
PixelShader* ShadersContent::colorPS;
PixelShader* ShadersContent::UIElementPS;
PixelShader* ShadersContent::PbrPS;

void ShadersContent::load(RenderWindow* renderWindow)
{
    D3D11_INPUT_ELEMENT_DESC defaultVertexShaderIED[5]
    { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    defaultVS = new VertexShader(renderWindow->graphics, L"Shaders//VertexShaders//DefaultVertexShader.hlsl", defaultVertexShaderIED, 5);
    defaultPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//DefaultPixelShader.hlsl");
    lightSourcePS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//LightSourcePS.hlsl");
    skyPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//SkyPS.hlsl");
    onlyTexturePS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//OnlyTexturePS.hlsl");
    TextPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//TextPS.hlsl");
    colorPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//ColorPS.hlsl");
    UIElementPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//UIElementPS.hlsl");
    PbrPS = new PixelShader(renderWindow->graphics, L"Shaders//PixelShaders//PbrPS.hlsl");
}
