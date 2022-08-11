#pragma once
#include "../IDrawable.h"
#include "../Transformable.h"
#include "../decl.h"
#include "../ModeledObject.h"

class UIElement : public Transformable, public IDrawable
{
public:
	ModeledObject* quad;
	double width;
	double height;
	DECL UIElement(RenderWindow* renderWindow);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
};

