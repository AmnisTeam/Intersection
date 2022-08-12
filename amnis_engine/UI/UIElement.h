#pragma once
#include "../IDrawable.h"
#include "../Transformable.h"
#include "../decl.h"
#include "../ModeledObject.h"

class UIElement : public Transformable, public IDrawable
{
public:
	ModeledObject* quad;
	double width;
	double height;
	float4 color = {1, 1, 1, 1};
	DECL UIElement(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL UIElement(RenderWindow* renderWindow, AmnModel* model, VertexShader* vertexShader, PixelShader* pixelShader);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
	AmnModel* quadModel;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
};

