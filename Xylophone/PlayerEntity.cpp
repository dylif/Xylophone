#include "PlayerEntity.hpp"

#include <functional>
#include <cmath>
#include "Macros+functions.hpp"

const float PlayerEntity::GRAVITY = SOUTH(9.8f * 24.0f);

bool PlayerEntity::Update(float elapsedtime, const std::list<std::shared_ptr<Entity>> &entities )
{
	auto getKey = std::bind(&olc::PixelGameEngine::GetKey, &this->engine, std::placeholders::_1);
	onGround = this->position.y >= groundY;
	
	for  (auto &a : entities) 
	{
		auto distance = this->position - a->position;
		if(a.get() != this)
		{
			
			if(abs(distance.y) <= a->height/2 + this->height/2 && abs(distance.x) <= a->width/2 + this->width/2)
			{
				if(this->selected)
					std::cout << distance.y << std::endl;
				if(signof(distance.y) == 1)
				{
					this->velocity.y *= -1;
					
				}
				else
				{
					this->velocity.y = 0;
					this->acceleration.y = 0;
					onSprite = a;
				}
			}
			if(abs(distance.x) <= a->width/2 + this->width/2 && abs(distance.y) <= a->height/2 + this->height/2 && (a.get() != this->onSprite.get() || onGround))
			{
					this->velocity.x *= -1;

					if(abs(this->velocity.x) > 0 && selected)
					{
						this->position.x = this->position.x + signof(this->velocity.x);
					}
			}
		}
	
	}
	// If we are in the are make sure our vertical accel is gravity
	if (onGround || onSprite)
		this->velocity.y = 0.0f;
	else
		this->acceleration.y = GRAVITY;
	
	
	if (selected) {
		// Jump if SPACE pressed and make sure to set onGround to false
		// for the rest of the logic
		if ((onSprite || onGround) && getKey(olc::UP).bPressed) {
			this->velocity.y = NORTH(maxSpeed.y);
			onGround = false;
			onSprite = nullptr;
		}

		// Change acceleration accordingly
		if (getKey(olc::LEFT).bHeld)
			this->acceleration.x = WEST(horizontalaccel);
		if (getKey(olc::RIGHT).bHeld)
			this->acceleration.x = EAST(horizontalaccel);
		
		
	} else {
		this->velocity.x = 0.0f;
	}
	if(!onGround && signof(this->velocity.x) != signof(this->acceleration.x))
    {
            this->acceleration.x *= 1.5;
    }
	// If nothing is pressed, we might have to apply friction
	if (!getKey(olc::LEFT).bHeld && !getKey(olc::RIGHT).bHeld) {
		this->acceleration.x = 0.0f;

			// Frictional updates
		if ((onGround || onSprite) && this->velocity.x != 0.0f) {
				// Save the sign to check if we need to stop moving
			auto sign = signof(this->velocity.x);
			this->velocity.x += -sign * frictionalaccel * elapsedtime;
				
				// If velocity changed signs, stop moving
			if (signof(this->velocity.x) != sign)
				this->velocity.x = 0.0f;
			}
		}
	
	

	// Calculate and vector add the change in velocity
	this->velocity += this->acceleration * elapsedtime;

	// Check if velocity is valid
	this->velocity.x = signof(this->velocity.x) * std::min(abs(this->velocity.x), abs(this->maxSpeed.x));
	this->velocity.y = signof(this->velocity.y) * std::min(abs(this->velocity.y), abs(this->maxSpeed.y));

	// Calculate and vector add the displacement
	this->position += this->velocity * elapsedtime;

	// Check if posiition is valid
	this->position.y = std::min(this->position.y, this->groundY);
	if (this->position.x > this->engine.ScreenWidth())
	{
		this->position.x = 0;
	}
	if (this->position.x < 0)
	{
		this->position.x = this->engine.ScreenWidth();
	}
	if(!onGround && signof(this->velocity.x) != signof(this->acceleration.x))
    {
            this->acceleration.x *= 2/3;
    }
	onSprite = nullptr;
	return true;
}