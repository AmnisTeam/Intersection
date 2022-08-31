#include "pch.h"
#include "Button.h"
#include "../RenderWindow.h"

Button::Button(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow)
{
	square = new ModeledObject(renderWindow, InnerModelsContent::square, vertexShader, pixelShader);
	//initColorSystem(square);
}

Button::Button(RenderWindow* renderWindow, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow)
{
	square = new ModeledObject(renderWindow, InnerModelsContent::square, vertexShader, pixelShader);
	initColorSystem(square, 0);
	setStyle(style);
}

Button::Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow)
{
	square = new ModeledObject(renderWindow, InnerModelsContent::square, vertexShader, pixelShader);
	initColorSystem(square, 0);
	setStyle(style);
	setPositionInPixels(positionInPixels);
	setSizeInPixels(sizeInPixels);
}

Button::Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style) : UIElement(renderWindow)
{
	square = new ModeledObject(renderWindow, InnerModelsContent::square, defaultVS, defaultPS);
	initColorSystem(square, 0);
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

	update(renderTarget, state);
	state.modelMatrix = state.modelMatrix * modelMatrix;
	renderTarget->draw(square, state);
}
