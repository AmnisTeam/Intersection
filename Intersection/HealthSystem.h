#pragma once

class IHealthable
{
public:
	virtual void OnDeath() = 0;
};

class HealthSystem
{
public:
	HealthSystem(IHealthable* healthable);
	
	void setHealth(float health);
	float getHealth();

	void setMaxHealth(float maxHealth);
	float getMaxHealth();

	void update();
protected:
	IHealthable* healthable_;
	float health_;
	float maxHealth_;
};