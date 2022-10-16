#pragma once
#include <Transformable.h>
#include <vector>

class IMovable
{
public:
	virtual void goToPosition(float3 position) = 0;
	virtual void addMoveTarget(float3 position) = 0;
	virtual void clearMoveTargets() = 0;
	virtual void updateMovableSystem(double deltaTime) = 0;
	virtual int getMoveTargetsCount() = 0;
};

class MoveSystem : public IMovable
{
public:
	std::vector<float3> moveTargets;
	float3 viewDirecton = { 0, 0, 1 };
	float3 velocity = {};
	float3 movement = {};
	double moveSpeed = 2;
	double turningSpeed = PI * 2;

	MoveSystem(Transformable* parent);

	// Унаследовано через IMovable
	virtual void goToPosition(float3 position) override;
	virtual void addMoveTarget(float3 position) override;
	virtual void clearMoveTargets() override;
	virtual void rotateViewDirectionTo(float3 dir, double deltaTime);
	virtual void updateMovableSystem(double deltaTime) override;
	virtual int getMoveTargetsCount() override;
	
	void setOldPosition(float3 oldPosition);
protected:
	Transformable* parent_;
	const float radiusOfPoint_ = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity_ = 900000;
	float3 oldPosition_;
	float3 tempPosition_;
	void movementToTargets();
	void moveTo(float3 const position);


};

