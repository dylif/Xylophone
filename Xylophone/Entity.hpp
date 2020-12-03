#pragma once

#include "olcPixelGameEngine.h"

class Entity : public olc::Sprite
{
public:
	Entity() = delete;

	Entity(const std::string &s, olc::PixelGameEngine &e,
		   olc::ResourcePack *r = nullptr, const olc::vf2d &p = { 0.0f, 0.0f }): 
		Sprite(s, r), engine(e), decal(this), position(p) { }

	// No need to worry about freeing memory, the olc::Sprite dtor will do that for us
	virtual ~Entity() = default;
	//static bool operator!=(Entity lhs, Entity rhs);
	// We provide basic versions of these functions should the user want a useless Entity
	virtual bool Update(float elapsedtime, const std::list<std::shared_ptr<Entity>> &entities );
	virtual bool Draw();

	olc::PixelGameEngine &engine;
	olc::Decal decal;
	olc::vf2d position;
};
