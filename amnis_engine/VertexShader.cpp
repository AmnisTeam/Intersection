#include "pch.h"
#include "VertexShader.h"

VertexShader::VertexShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint, LPCSTR pTarget)
{
    HRESULT hr = D3DCompileFromFile(pFileName, NULL, NULL, pEntrypoint, pTarget, NULL, NULL, &vertexShaderCode, NULL);
    if (FAILED(hr)) throw;

    hr = graphics->device->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
    if (FAILED(hr)) throw;
}

VertexShader::VertexShader(Graphics* graphics, LPCWSTR pFileName, D3D11_INPUT_ELEMENT_DESC* elementDesc, int elementsCount, LPCSTR pEntrypoint, LPCSTR pTarget)
{
    HRESULT hr = D3DCompileFromFile(pFileName, NULL, NULL, pEntrypoint, pTarget, NULL, NULL, &vertexShaderCode, NULL);
    if (FAILED(hr)) throw;

    hr = graphics->device->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
    if (FAILED(hr)) throw;

    hr = graphics->device->CreateInputLayout(elementDesc, elementsCount, GetCodeBufferPointer(), GetCodeBufferSize(), &inputLayout);
    if (FAILED(hr)) throw;
}

ID3D11VertexShader* VertexShader::get()
{
    return vertexShader;
}

ID3D11VertexShader** VertexShader::getpp()
{
    return &vertexShader;
}

ID3D11InputLayout* VertexShader::getLayoutp()
{
    return inputLayout;
}

ID3D11InputLayout** VertexShader::getLayoutpp()
{
    return &inputLayout;
}

LPVOID VertexShader::GetCodeBufferPointer()
{
    return vertexShaderCode->GetBufferPointer();
}

SIZE_T VertexShader::GetCodeBufferSize()
{
    return vertexShaderCode->GetBufferSize();
}

void VertexShader::setVertexShader(Graphics* graphics)
{
    graphics->deviceCon->VSSetShader(get(), NULL, NULL);
}

void VertexShader::setLayout(Graphics* graphics)
{
    graphics->deviceCon->IASetInputLayout(getLayoutp());
}

void VertexShader::setVertexShaderAndLayout(Graphics* graphics)
{
    setLayout(graphics);
    setVertexShader(graphics);
}
