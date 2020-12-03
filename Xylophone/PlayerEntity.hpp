#pragma once

#include "Entity.hpp"

//TODO: Update constructor to include fritional and horizontal acceleration
class PlayerEntity : public Entity {
public:
	static const float GRAVITY;

	PlayerEntity(const std::string &s, olc::PixelGameEngine &e, olc::vf2d m, olc::ResourcePack *r = nullptr, 
				 const olc::vf2d &p = { 0.0f, 0.0f }, olc::vf2d v = { 0.0f, 0.0f }, olc::vf2d a = { 0.0f, GRAVITY }):
		Entity(s, e, r, p), maxSpeed(m), groundY(getGroundLevel<float>()) { }
	
	bool Update(float elapsedtime, const std::list<std::shared_ptr<Entity>> &entities) override;

	olc::vf2d maxSpeed;
	olc::vf2d inputAcceleration;
	olc::vf2d friction;
	bool selected = false;

private:
	template <class T> T getGroundLevel()
	{
		return static_cast<T>(this->engine.ScreenHeight() - this->height);
	}
	const float frictionalaccel = 750;
	const float horizontalaccel = 250;
	const float groundY;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	bool onGround = false;
	 std::shared_ptr<Entity> onSprite = nullptr;
};