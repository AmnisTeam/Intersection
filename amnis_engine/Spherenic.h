#pragma once
#include "Transformable.h"
#include "IDrawable.h"
#include "Sphere.h"

class Spherenic : public Transformable, public IDrawable
{
public:
	int countSpheres = 5;
	Sphere** sphere;

	Spherenic(RenderWindow* renderWindow);

	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

