#include "pch.h"
#include "DefaultVertexShader.h"

DefaultVertexShader::DefaultVertexShader(Graphics* graphics, LPCWSTR shaderPath) : VertexShader(graphics, shaderPath)
{
    D3D11_INPUT_ELEMENT_DESC elementDesc[5]
    { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    HRESULT hr = graphics->device->CreateInputLayout(elementDesc, 5, GetCodeBufferPointer(), GetCodeBufferSize(), &inputLayout);
    if (FAILED(hr)) throw;
}