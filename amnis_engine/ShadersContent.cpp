#include "pch.h"
#include "ShadersContent.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShadersContent::ShadersContent(Graphics* graphics)
{
	this->graphics = graphics;

    D3D11_INPUT_ELEMENT_DESC defaultVertexShaderIED[5]
    { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    defaultVS = new VertexShader(graphics, L"Shaders//VertexShaders//DefaultVertexShader.hlsl", defaultVertexShaderIED, 5);
    defaultPS = new PixelShader(graphics, L"Shaders//PixelShaders//DefaultPixelShader.hlsl");
    lightSourcePS = new PixelShader(graphics, L"Shaders//PixelShaders//LightSourcePS.hlsl");
    skyPS = new PixelShader(graphics, L"Shaders//PixelShaders//SkyPS.hlsl");
}

void ShadersContent::loadShaders()
{
}
