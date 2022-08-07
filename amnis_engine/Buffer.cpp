#include "pch.h"
#include "Buffer.h"

Buffer::Buffer(Graphics* graphics, UINT BindFlags, void* pData, UINT ByteWidth, D3D11_USAGE usage, UINT CPUAccessFlags, UINT MiscFlags, UINT StructureByteStride)
{
    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = ByteWidth;
    bufferDesc.Usage = usage;
    bufferDesc.BindFlags = BindFlags;
    bufferDesc.CPUAccessFlags = CPUAccessFlags;
    bufferDesc.MiscFlags = MiscFlags;
    bufferDesc.StructureByteStride = StructureByteStride;

    HRESULT hr;
    if (pData) 
    {
        D3D11_SUBRESOURCE_DATA sd{};
        sd.pSysMem = pData;
        hr = graphics->device->CreateBuffer(&bufferDesc, &sd, &buffer);
    }
    else
    {
        D3D11_SUBRESOURCE_DATA sd{};
        sd.pSysMem = pData;
        hr = graphics->device->CreateBuffer(&bufferDesc, NULL, &buffer);
    }
    if (FAILED(hr)) throw;
}

ID3D11Buffer* Buffer::get()
{
    return buffer;
}

ID3D11Buffer** Buffer::getpp()
{
    return &buffer;
}
