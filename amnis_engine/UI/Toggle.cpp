#include "pch.h"
#include "Toggle.h"

Toggle::Toggle(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
}

void Toggle::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	UIElement::draw(renderTarget, state);
}