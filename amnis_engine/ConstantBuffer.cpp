#include "pch.h"
#include "ConstantBuffer.h"
#include "RenderWindow.h"

ConstantBuffer::ConstantBuffer(Graphics* graphics)
{
	this->graphics = graphics;
}

void ConstantBuffer::init()
{
	unsigned int size = 0;
	for (int i = 0; i < values.size(); i++)
		size += values[i].size;

	Buffer::init(graphics, D3D11_BIND_CONSTANT_BUFFER, values.data(), size, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
}

void ConstantBuffer::add(void* value, const char* key, unsigned int const size)
{
	void* data = malloc(size);
	if (value)
		memcpy(data, value, size);

	values.push_back(ConstantElement{ key , data , size });
}

void ConstantBuffer::updateValue(unsigned int id, void* value)
{
	if (id >= values.size())
		throw;
	memcpy(values[id].data, value, values[id].size);
}

void ConstantBuffer::updateBuffer()
{
	D3D11_MAPPED_SUBRESOURCE ms{};
	graphics->deviceCon->Map(get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	char* lastPos = (char*)ms.pData;
	for (int i = 0; i < values.size(); i++)
	{
		memcpy(lastPos, values[i].data, values[i].size);
		lastPos += values[i].size;
	}

	graphics->deviceCon->Unmap(get(), NULL);
}

void ConstantBuffer::PSSet(unsigned int slot)
{
	graphics->deviceCon->PSSetConstantBuffers(slot, 1, getpp());
}

void ConstantBuffer::VSSet(unsigned int slot)
{
	graphics->deviceCon->VSSetConstantBuffers(slot, 1, getpp());
}
