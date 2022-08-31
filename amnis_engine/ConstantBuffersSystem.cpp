#include "pch.h"
#include "ConstantBuffersSystem.h"
#include "RenderWindow.h"

ConstantBuffersSystem::ConstantBuffersSystem(RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
}

void ConstantBuffersSystem::VSSet(ConstantBuffer* constantBuffer, unsigned int const slot)
{
	constantBuffersVS[slot] = constantBuffer;
}

void ConstantBuffersSystem::PSSet(ConstantBuffer* constantBuffer, unsigned int const slot)
{
	constantBuffersPS[slot] = constantBuffer;
}

void ConstantBuffersSystem::VSAdd(unsigned int const slot)
{
	ConstantBuffer* constantBufferVS = new ConstantBuffer(renderWindow->graphics);
	VSSet(constantBufferVS, slot);
}

void ConstantBuffersSystem::PSAdd(unsigned int const slot)
{
	ConstantBuffer* constantBufferPS = new ConstantBuffer(renderWindow->graphics);
	PSSet(constantBufferPS, slot);
}

void ConstantBuffersSystem::VSAddValue(unsigned int slot, void* value, const char* key, unsigned int const size)
{
	if (constantBuffersVS[slot] == nullptr)
		VSAdd(slot);

	constantBuffersVS[slot]->add(value, key, size);
}

void ConstantBuffersSystem::PSAddValue(unsigned int slot, void* value, const char* key, unsigned int const size)
{
	if (constantBuffersPS[slot] == nullptr)
		PSAdd(slot);

	constantBuffersPS[slot]->add(value, key, size);
}

void ConstantBuffersSystem::VSUpdateValue(unsigned int const slot, const char* key, void* data)
{
	if (constantBuffersVS[slot]->values.size() > 0)
	{
		if (constantBuffersVS[slot]->buffer == nullptr)
			VSInit(slot);
	}
	else throw;

	constantBuffersVS[slot]->updateValue(key, data);
}

void ConstantBuffersSystem::PSUpdateValue(unsigned int const slot, const char* key, void* data)
{
	if (constantBuffersPS[slot]->values.size() > 0)
	{
		if (constantBuffersPS[slot]->buffer == nullptr)
			PSInit(slot);
	}
	else throw;

	constantBuffersPS[slot]->updateValue(key, data);
}

void ConstantBuffersSystem::VSInit(unsigned int const slot)
{
	constantBuffersVS[slot]->init();
}

void ConstantBuffersSystem::PSInit(unsigned int const slot)
{
	constantBuffersPS[slot]->init();
}

void ConstantBuffersSystem::updateAndSetAll()
{
	for (auto it = constantBuffersVS.begin(); it != constantBuffersVS.end(); it++)
	{
		it->second->updateBuffer();
		it->second->VSSet(it->first);
	}

	for (auto it = constantBuffersPS.begin(); it != constantBuffersPS.end(); it++)
	{
		it->second->updateBuffer();
		it->second->PSSet(it->first);
	}
}
