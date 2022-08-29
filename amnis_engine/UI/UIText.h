#pragma once
#include "../text.h"
#include "UIElement.h"
#include "../decl.h"

class UIText : public UIElement
{
public:
	// Scaling directly from text is broken so you don't need to use it until this is fixed
	Text* text;
	DECL UIText(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL ~UIText();
	DECL virtual void setSizeInPixels(float2 size) override;
	//DECL virtual void setSizeInScreenSize(float2 size) override;
	virtual void DECL update(RenderTarget* renderTarget, RenderState state) override;
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
};

