#include "pch.h"
#include "PixelShader.h"

PixelShader::PixelShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint, LPCSTR pTarget)
{
    HRESULT hr = D3DCompileFromFile(pFileName, NULL, NULL, pEntrypoint, pTarget, NULL, NULL, &pixelShaderCode, NULL);
    if (FAILED(hr)) throw;

    hr = graphics->device->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
    if (FAILED(hr)) throw;
}

ID3D11PixelShader* PixelShader::get()
{
    return pixelShader;
}

ID3D11PixelShader** PixelShader::getpp()
{
    return &pixelShader;
}

LPVOID PixelShader::GetCodeBufferPointer()
{
    return pixelShaderCode->GetBufferPointer();
}

SIZE_T PixelShader::GetCodeBufferSize()
{
    return pixelShaderCode->GetBufferSize();
}

void PixelShader::setPixelShader(Graphics* graphics)
{
    graphics->deviceCon->PSSetShader(pixelShader, NULL, NULL);
}