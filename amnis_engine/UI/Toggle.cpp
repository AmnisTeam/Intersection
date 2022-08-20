#include "pch.h"
#include "Toggle.h"

Toggle::Toggle(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
}

Toggle::Toggle(RenderWindow* renderWindow, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
	setStyle(style);
}

Toggle::Toggle(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow, vertexShader, pixelShader)
{
	setStyle(style);
	setPositionInPixels(positionInPixels);
	setSizeInPixels(sizeInPixels);
}

Toggle::Toggle(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style) : UIElement(renderWindow)
{
	setStyle(style);
	setPositionInPixels(positionInPixels);
	setSizeInPixels(sizeInPixels);
}



void Toggle::addDownEvent(Event* event)
{
	downEvents.push_back(event);
}

void Toggle::addUpEvent(Event* event)
{
	upEvents.push_back(event);
}

void Toggle::addPressedEvent(Event* event)
{
	pressedEvents.push_back(event);
}

void Toggle::executeDownEvents()
{
	for (int i = 0; i < downEvents.size(); i++)
		downEvents[i]->execute();
}

void Toggle::executeUpEvents()
{
	for (int i = 0; i < upEvents.size(); i++)
		upEvents[i]->execute();
}

void Toggle::executePressedEvents()
{
	for (int i = 0; i < pressedEvents.size(); i++)
		pressedEvents[i]->execute();
}

void Toggle::setState(bool state)
{
	this->state = state;
}

bool Toggle::getState() const
{
	return state;
}

void Toggle::updateColor()
{
	if(!state)
		UIElement::updateColor();
	else
	{
		if (getPressed())
		{
			quad->PSConstBufUpdateValue(0, 0, &onPressColor);
		}
		else
		{
			if (getHover())
				quad->PSConstBufUpdateValue(0, 0, &onHoverColor);
			else
				quad->PSConstBufUpdateValue(0, 0, &onColor);
		}
	}
}

void Toggle::draw(RenderTarget* renderTarget, RenderState state)
{
	if (onDown())
	{
		executeDownEvents();
	}
	if (onUp())
	{
		this->state = !this->state;
		executeUpEvents();
	}
	if(getPressed()) executePressedEvents();

	UIElement::draw(renderTarget, state);
}