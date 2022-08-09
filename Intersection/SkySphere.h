#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Sphere.h"
#include "decl.h"

class SkySphere : public Transformable, public IDrawable
{
public:
	Sphere* sphere;
	DECL SkySphere(RenderWindow* renderWindow, Texture* texture);
	DECL ~SkySphere();
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
};