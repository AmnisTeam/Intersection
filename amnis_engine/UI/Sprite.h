#pragma once
#include "UIElement.h"
#include "../decl.h"

class Sprite : public UIElement, public IDrawable
{
public:
	ModeledObject* square;
	DECL Sprite(RenderWindow* renderWindow, Texture* texture, float4 textureRect, VertexShader* vertexShader, PixelShader* pixelShader);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
};

