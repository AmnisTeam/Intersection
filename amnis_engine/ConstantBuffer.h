#pragma once
#include "Buffer.h"
#include <vector>
#include "AMNFormat.h"

class ConstantBuffer : public Buffer
{
public:
	struct ConstantElement
	{
		const char* key;
		void* data;
		unsigned int size;
	};
	ConstantBuffer(Graphics* graphics);
	void init();
	void add(void* value, const char* key, unsigned int const size);
	void updateValue(unsigned int id, void* value);
	void updateBuffer();
	void VSSet(unsigned int slot);
	void PSSet(unsigned int slot);
private:
	Graphics* graphics;
	std::vector<ConstantElement> values;
};

