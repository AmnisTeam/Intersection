#pragma once
#include "UIElement.h"
#include "../decl.h"
#include <vector>
#include "../Event.h"

class Button : public UIElement
{
public:
	DECL Button(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void addEvent(Event* event);
	DECL void executeEvents();
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	std::vector<Event*> events;
};

