#pragma once
#include "UIElement.h"
#include "../Event.h"
#include <vector>

class Toggle : public UIElement
{
public:
	DECL void addDownEvent(Event* event);
	DECL void addUpEvent(Event* event);
	DECL void addPressedEvent(Event* event);

	DECL void executeDownEvents();
	DECL void executeUpEvents();
	DECL void executePressedEvents();

	DECL void setState(bool state);
	DECL bool getState() const;

	DECL virtual void updateColor() override;

	DECL Toggle(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	bool state = false;
	std::vector<Event*> downEvents;
	std::vector<Event*> upEvents;
	std::vector<Event*> pressedEvents;
};