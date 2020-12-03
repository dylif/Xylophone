#include "Engine.hpp"

#include "olcPixelGameEngine.h"

#include "PlayerEntity.hpp"

const std::string Engine::APP_NAME = "game";

const std::string Engine::RES_BLUE_1 = "blue1.png";
const std::string Engine::RES_BLUE_2 = "blue2.png";
const std::string Engine::RES_RED_1 = "red1.png";
const std::string Engine::RES_RED_2 = "red2.png";

Engine::Engine()
{
	sAppName = Engine::APP_NAME;
}

bool Engine::OnUserCreate()
{
	mortal = std::make_unique<std::list<std::shared_ptr<Entity>>>();

	return true;
}

bool Engine::OnUserUpdate(float elapsedTime)
{
	// If left mouse pressed, spawn an Entity
	if (GetMouse(0).bPressed) {
		auto &e = static_cast<PlayerEntity &>(*(mortal->emplace_back(std::make_unique<PlayerEntity>(RES_BLUE_1, *this, olc::vf2d(200, 250), nullptr))));
		olc::vf2d center = getCenter(e);
		olc::vf2d mouse = this->getMousePos<float>();
		e.position = mouse - center;
		e.selected = true;
		if (mortal->size() > 1)
			static_cast<PlayerEntity &>((*(*(----mortal->end())))).selected = false;
			
	}

	// If middle mouse pressed, clear the screen
	if (GetMouse(2).bPressed)
		mortal->clear();

	// Undo function
	if (GetKey(olc::CTRL).bHeld && GetKey(olc::Z).bPressed) {
		if (!mortal->empty()) {
			mortal->pop_back();
			if (!mortal->empty())
				static_cast<PlayerEntity &>(*mortal->back()).selected = true;
		}
	}

	// Update Entity list
	for (auto it = mortal->begin(); it != mortal->end(); ) {
		bool success = (*it)->Update(elapsedTime, *mortal);
		if (!success)
			it = mortal->erase(it);
		else
			++it;
	}

	// Draw Entities
	for (auto &s : *mortal)
		s->Draw();
		
	return true;
}