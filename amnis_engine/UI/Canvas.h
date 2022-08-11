#pragma once
#include "UIElement.h"
#include <vector>

class Canvas : public UIElement
{
public:
	DECL Canvas(RenderWindow* renderWindow);
	DECL void addUIElement(UIElement* element);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	std::vector<UIElement*> uiElements;
};

