#pragma once
#include "UIElement.h"

class Toggle : public UIElement
{
public:
	DECL Toggle(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
};