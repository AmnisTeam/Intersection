#pragma once
#include "Transformable.h"
#include "IDrawable.h"
#include "Sphere.h"
#include "decl.h"

class Spherenic : public Transformable, public IDrawable
{
public:
	int countSpheres = 5;
	Sphere** sphere;

	DECL Spherenic(RenderWindow* renderWindow);
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

