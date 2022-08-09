#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include <RenderWindow.h>

class Entity : public Transformable, public IDrawable
{
public:
	ModeledObject* model;
	Entity(RenderWindow* renderWindow, AmnModel* model);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};