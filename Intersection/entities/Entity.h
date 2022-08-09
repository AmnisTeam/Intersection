#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include <RenderWindow.h>

class Entity : public Transformable, public IDrawable
{
public:
	ModeledObject* model;
	float3 viewDirecton = {0, 0, 1};
	double3 velocity = {};
	double moveSpeed = 1;
	double turningSpeed = PI * 0.5;
	double3 pointsToGoTo;
	Entity(RenderWindow* renderWindow, Model* model);
	void goToPosition(float3 position);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};