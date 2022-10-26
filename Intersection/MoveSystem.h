#pragma once
#include <mymath.h>
#include <vector>

class MoveSystem;
class ObjectInWorld;

class IMovable
{
public:
	virtual MoveSystem* getMoveSystem() = 0;
};

class MoveSystem
{
public:
	std::vector<float3> moveTargets;
	float3 viewDirecton = { 0, 0, 1 };
	float3 velocity = {};
	float3 movement = {};
	double moveSpeed = 2;
	double turningSpeed = PI * 2;

	MoveSystem(ObjectInWorld* parent);

	// Унаследовано через IMovable
	void goToPosition(float3 position);
	void addMoveTarget(float3 position);
	void clearMoveTargets();
	void rotateViewDirectionTo(float3 dir, double deltaTime);
	void updateMovableSystem(double deltaTime);
	int getMoveTargetsCount();
	void goToPositionAstar(float3 position);
	
	void setOldPosition(float3 oldPosition);
protected:
	ObjectInWorld* parent_;
	const float radiusOfPoint_ = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity_ = 900000;
	float3 oldPosition_;
	float3 tempPosition_;
	void movementToTargets();
	void moveTo(float3 const position);


};

