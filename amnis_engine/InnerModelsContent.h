#pragma once
#include "AmnModel.h"
#include "decl.h"

class InnerModelsContent
{
public:
	static AmnModel* square;
	static DECL void load(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
private:
	static std::vector<Vertex> vertices;
	static std::vector<int> indices;
	static DECL void initSquare(std::vector<Vertex>* vertices, std::vector<int>* indices);
};

