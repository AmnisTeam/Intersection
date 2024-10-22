#include "Entity.h"
#include "../World.h"

Entity::Entity(World* world, AmnModel* model, float health, float mana) : Commandable(world, health, mana)
{
	this->model = new ModeledObject(world->renderWindow, model);
	oldPosition = getPosition();
	this->model->setTexture(TexturesContent::flatNormalMap, 1);

	boxCollider = new BoxCollider(getOrigin(), getPosition(), getScale());
	moveSystem_ = new MoveSystem(this);
}

MoveSystem* Entity::getMoveSystem()
{
	return moveSystem_;
}

bool Entity::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	return boxCollider->raycast(ray, hitPoint, colliderState);
}

//void Entity::setPositionWithoutSettingOldPosition(float3 position)
//{
//	Transformable::setPosition(position);
//	boxCollider->setPosition(position);
//}

void Entity::update()
{
	Commandable::update();
	oldPosition = getPosition();

	moveSystem_->updateMovableSystem(world->renderWindow->graphics->deltaTime);

	setPosition(getPosition() + moveSystem_->velocity * world->renderWindow->graphics->deltaTime);
	collisionWithBuildings();
}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	renderTarget->draw(model, state);
}

void Entity::setAttackTarget(Entity* entity)
{
	attackTarget_ = entity;
}

Entity::~Entity()
{

}

void Entity::collisionWithBuildings()
{
	int2 entityGrid = mymath::getGridId(getPosition(), {world->grid->sizeElementX, world->grid->sizeElementY});

	for(int x = entityGrid.x - ceil(5); x <= entityGrid.x + ceil(5); x++)
		for (int y = entityGrid.y - ceil(5); y <= entityGrid.y + ceil(5); y++)
		{
			GridElement* gridElement;
			world->grid->getGridElement(x, y, &gridElement);
			if (GridElement::isWall(gridElement))
			{
				float radiusWall = world->grid->sizeElementX / 2;
				float radiusEntity = radiusCollision;

				float3 entityPosition = getPosition();
				float2 wallCenter = {x * world->grid->sizeElementX + world->grid->sizeElementX / 2,
									 y * world->grid->sizeElementY - world->grid->sizeElementX / 2 };

				float2 entityCenter = { entityPosition.x, 
									    entityPosition.z };
				
				float distance = mymath::getLength(wallCenter - entityCenter);
				if (distance <= radiusWall + radiusEntity) //������
				{
					float offset = 0.0001f;
					float2 direction = mymath::normalize(entityCenter - wallCenter);
					entityCenter = wallCenter + direction * (radiusWall + radiusEntity + offset);
					setPosition({entityCenter.x, entityPosition.y, entityCenter.y});
				}

				//Building* building = gridElement->getBuilding();
				//if (building != nullptr)
				//{
				//	float3 entityPosition = getPosition();
				//	FloatRect entityRect({ entityPosition.x - radiusCollision, -(entityPosition.z + radiusCollision) }, { radiusCollision * 2, radiusCollision * 2 });
				//	FloatRect buildingRect({building->posX * world->grid->sizeElementX, -building->posY * world->grid->sizeElementY }, 
				//						   {building->width * world->grid->sizeElementX, building->height * world->grid->sizeElementY });		
				//	if (entityRect.intersect(buildingRect))
				//	{
				//		float3 deltaPosition = entityPosition - oldPosition;
				//		entityRect.collision({deltaPosition.x, -deltaPosition.z}, buildingRect);
				//		setPosition({entityRect.position.x + radiusCollision, entityPosition.y, -(entityRect.position.y + radiusCollision)});
				//	}
				//}
			}

		}
}

void Entity::death()
{
	world->deleteEntity(this);
}

void Entity::setPosition(float3 position)
{
	Transformable::setPosition(position);
	boxCollider->setPosition(position);
}

void Entity::setRotation(float3 rotation)
{
	Transformable::setRotation(rotation);
	boxCollider->setRotation(rotation);
}

void Entity::setScale(float3 scale)
{
	Transformable::setScale(scale);
	boxCollider->setScale(scale);
}

void Entity::setOrigin(float3 origin)
{
	Transformable::setOrigin(origin);
	//boxCollider->setOrigin(origin);
}