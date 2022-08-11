#pragma once
#include <vector>
#include "decl.h"

class VertexShader;
class PixelShader;
class Graphics;

class ShadersContent
{
public:
	VertexShader* defaultVS;
	PixelShader* defaultPS;
	PixelShader* lightSourcePS;
	PixelShader* skyPS;
	PixelShader* onlyTexturePS;
	DECL ShadersContent(Graphics* graphics);
	DECL void loadShaders();
private:
	Graphics* graphics;
};

