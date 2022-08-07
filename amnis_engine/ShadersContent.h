#pragma once
#include <vector>

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
	ShadersContent(Graphics* graphics);
	void loadShaders();
private:
	Graphics* graphics;
};

