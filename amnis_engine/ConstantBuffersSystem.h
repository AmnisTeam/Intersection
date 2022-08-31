#pragma once
#include "decl.h"
#include "ConstantBuffer.h"

class RenderWindow;
class ConstantBuffersSystem
{
public:
	DECL ConstantBuffersSystem(RenderWindow* renderWindow);
	DECL void VSAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void PSAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void VSUpdateValue(unsigned int const slot, const char* key, void* data);
	DECL void PSUpdateValue(unsigned int const slot, const char* key, void* data);
	DECL void VSInit(unsigned int const slot);
	DECL void PSInit(unsigned int const slot);

	DECL void updateAndSetAll();
private:
	RenderWindow* renderWindow;
	std::map<unsigned int, ConstantBuffer*> constantBuffersVS;
	std::map<unsigned int, ConstantBuffer*> constantBuffersPS;
	DECL void VSSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void PSSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void VSAdd(unsigned int const slot);
	DECL void PSAdd(unsigned int const slot);
};

