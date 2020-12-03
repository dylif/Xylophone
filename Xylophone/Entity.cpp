#include "Entity.hpp"

bool Entity::Update(float elapsedTime, const std::list<std::shared_ptr<Entity>> &entities)
{ 
	return true;
}
bool Entity::Draw()
{
	this->decal.Update();
	engine.DrawDecal(this->position, &(this->decal));

	return true;
}