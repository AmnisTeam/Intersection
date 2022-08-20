#pragma once
#include "Transformable.h";
#include "IDrawable.h"
#include "Font.h"
#include "ModeledObject.h"
#include "UI/UIElement.h"
#include "decl.h"

class Text : public Transformable, public IDrawable
{
public:
	ModeledObject* modelObject;
	DECL Text(RenderWindow* renderWindow, std::string text, Font* font, VertexShader* vertexShader, PixelShader* pixelShader);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
	AmnModel* model;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	
};

