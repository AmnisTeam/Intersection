#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "ModeledObject.h"
#include "RenderWindow.h"
#include "ModelsContent.h"

class Sphere : public Transformable, public IDrawable
{
public:
	ModeledObject* model;
	Sphere(RenderWindow* renderWindow);
	RenderWindow* getRenderWindow();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
};

