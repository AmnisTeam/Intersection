#include "pch.h"
#include "SampleState.h"

SampleState::SampleState(Graphics* graphics)
{
    D3D11_SAMPLER_DESC samplerDesc{};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0;
    samplerDesc.MaxAnisotropy = 0;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.BorderColor[4] = {0};
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    HRESULT hr = graphics->device->CreateSamplerState(&samplerDesc, &sampleState);
    if (FAILED(hr)) throw;
}

void SampleState::set(Graphics* graphics)
{
    graphics->deviceCon->PSSetSamplers(0, 1, &sampleState);
}
