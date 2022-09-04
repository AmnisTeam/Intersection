#include "HealthSystem.h"
#include "entities/Entity.h"

HealthSystem::HealthSystem(IHealthable* healthable)
{
	healthable_ = healthable;
}

void HealthSystem::setHealth(float health)
{
	health_ = health;
}

float HealthSystem::getHealth()
{
	return health_;
}

void HealthSystem::setMaxHealth(float maxHealth)
{
	maxHealth_ = maxHealth;
}

float HealthSystem::getMaxHealth()
{
	return maxHealth_;
}

void HealthSystem::update()
{
	if (health_ <= 0)
		healthable_->OnDeath();
}