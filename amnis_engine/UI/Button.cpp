#include "pch.h"
#include "Button.h"
#include "../RenderWindow.h"

Button::Button(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
}

Button::Button(RenderWindow* renderWindow, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
	setStyle(style);
}

Button::Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
	setStyle(style);
	setPositionInPixels(positionInPixels);
	setSizeInPixels(sizeInPixels);
}

Button::Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style) : UIElement(renderWindow)
{
	setStyle(style);
	setPositionInPixels(positionInPixels);
	setSizeInPixels(sizeInPixels);
}

Button::Button(RenderWindow* renderWindow, UIStyle style) : UIElement(renderWindow)
{
	setStyle(style);
}

void Button::addEvent(Event* event)
{
	events.push_back(event);
}

void Button::executeEvents()
{
	for (int i = 0; i < events.size(); i++)
		events[i]->execute();
}

void Button::draw(RenderTarget* renderTarget, RenderState state)
{
	if (onDown())
		executeEvents();

	state.modelMatrix = modelMatrix * state.modelMatrix;
	UIElement::draw(renderTarget, state);
}
