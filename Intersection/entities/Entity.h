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
	float3 velocity = {};
	double moveSpeed = 2;
	double turningSpeed = PI * 0.5;
	std::vector<float3> moveTargets;
	Entity(RenderWindow* const renderWindow, Model* const model);
	void goToPosition(float3 position);
	void addMoveTarget(float3 position);
	void clearMoveTargets();
	void rotateViewDirectionTo(float3 dir);
	virtual void update();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
	float radiusOfPoint = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity = 900000;
	float3 oldPosition;
	void movementToTargets();
	void movementToTargets2();
	void moveTo(float3 const position);
};