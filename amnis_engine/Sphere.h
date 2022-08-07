#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "ModeledObject.h"
#include "RenderWindow.h"
#include "decl.h"

class Sphere : public Transformable, public IDrawable
{
public:
	ModeledObject* model;
	DECL Sphere(RenderWindow* renderWindow);
	DECL RenderWindow* getRenderWindow();
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
};

