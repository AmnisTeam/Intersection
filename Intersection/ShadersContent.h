#pragma once
#include <vector>
#include "decl.h"

class VertexShader;
class PixelShader;
class RenderWindow;

class ShadersContent
{
public:
	static VertexShader* defaultVS;
	static PixelShader* defaultPS;
	static PixelShader* lightSourcePS;
	static PixelShader* skyPS;
	static PixelShader* onlyTexturePS;

	static void load(RenderWindow* renderWindow);

};

