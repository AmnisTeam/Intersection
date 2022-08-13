#include "pch.h"
#include "Button.h"
#include "../RenderWindow.h"

Button::Button(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
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
