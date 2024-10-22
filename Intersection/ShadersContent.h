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
	static PixelShader* TextPS;
	static PixelShader* colorPS;
	static PixelShader* UIElementPS;

	static void load(RenderWindow* renderWindow);

};

