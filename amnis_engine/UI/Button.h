#pragma once
#include "UIElement.h"
#include "../decl.h"
#include <vector>
#include "../Event.h"

class Button : public UIElement
{
public:
	ModeledObject* square;
	DECL Button(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Button(RenderWindow* renderWindow, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Button(RenderWindow* renderWindow, float2 positionInPixels, float2 sizeInPixels, UIStyle style);
	DECL Button(RenderWindow* renderWindow, UIStyle style);
	DECL void addEvent(Event* event);
	DECL void executeEvents();
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	std::vector<Event*> events;
};

