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
	for (auto it = values.begin(); it != values.end(); it++)
		size += it->second.size;
	
	void* memory = malloc(size);
	for (auto it = values.begin(); it != values.end(); it++)
		memcpy((char*)memory + it->second.sizeToElement, it->second.data, it->second.size);	

	Buffer::init(graphics, D3D11_BIND_CONSTANT_BUFFER, memory, size, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
}

void ConstantBuffer::add(void* value, const char* key, unsigned int const size)
{
	void* data = malloc(size);
	if (value)
		memcpy(data, value, size);

	values[key] = ConstantElement{ key, data , size, lastSizeSum };
	lastSizeSum += size;
}

void ConstantBuffer::updateValue(const char* key, void* value)
{
	if(values[key].data)
		memcpy(values[key].data, value, values[key].size);
}

void ConstantBuffer::updateBuffer()
{
	//D3D11_MAPPED_SUBRESOURCE ms{};
	//graphics->deviceCon->Map(get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	//char* lastPos = (char*)ms.pData;
	//for (int i = 0; i < values.size(); i++)
	//{
	//	memcpy(lastPos, values[i].data, values[i].size);
	//	lastPos += values[i].size;
	//}
	//graphics->deviceCon->Unmap(get(), NULL);

	D3D11_MAPPED_SUBRESOURCE ms{};
	graphics->deviceCon->Map(get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	char* memory = (char*)ms.pData;
	for (auto it = values.begin(); it != values.end(); it++)
		memcpy(memory + it->second.sizeToElement, it->second.data, it->second.size);

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