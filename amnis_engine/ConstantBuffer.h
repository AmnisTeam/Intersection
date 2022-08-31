#pragma once
#include "Buffer.h"
#include <vector>
#include <map>
#include "AMNFormat.h"
#include "decl.h"


class ConstantBuffer : public Buffer
{
public:
	friend class ConstantBuffersSystem;
	struct ConstantElement
	{
		const char* key;
		void* data;
		unsigned int size;
		unsigned int sizeToElement;
	};
	DECL ConstantBuffer(Graphics* graphics);
	DECL void init();
	DECL void add(void* value, const char* key, unsigned int const size);
	DECL void updateValue(const char* key, void* value);
	DECL void updateBuffer();
	DECL void VSSet(unsigned int slot);
	DECL void PSSet(unsigned int slot);
private:
	Graphics* graphics;
	std::map<std::string, ConstantElement> values;
	unsigned int lastSizeSum = 0;
};

