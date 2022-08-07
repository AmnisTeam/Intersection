#include "pch.h"
#include "VSLightSource.h"

VSLightSource::VSLightSource(Graphics* graphics, LPCWSTR VSLightSourcePath) : VertexShader(graphics, VSLightSourcePath)
{
    D3D11_INPUT_ELEMENT_DESC elementDesc[1]
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    HRESULT hr = graphics->device->CreateInputLayout(elementDesc, 1, GetCodeBufferPointer(), GetCodeBufferSize(), &inputLayout);
    if (FAILED(hr)) throw;
}
