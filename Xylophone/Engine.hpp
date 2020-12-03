#pragma once

#include <string>
#include <list>

#include "olcPixelGameEngine.h"

#include "Entity.hpp"

inline olc::vf2d getCenter(const olc::Sprite &s)
{
	return { s.width / 2.0f, s.height / 2.0f };
}

class Engine : public olc::PixelGameEngine {
public:
	static const std::string APP_NAME;
	static const std::string RES_BLUE_1;
	static const std::string RES_BLUE_2;
	static const std::string RES_RED_1;
	static const std::string RES_RED_2;

	Engine();

	bool OnUserCreate() override;
	bool OnUserUpdate(float timeElapsed) override;

	// Helper function to get the mouse position as a vector
	template <class T> olc::v2d_generic<T> getMousePos()
	{
		return { static_cast<T>(this->GetMouseX()), static_cast<T>(this->GetMouseY()) };
	}

private:
	std::string selected = RES_BLUE_2;
	olc::vf2d bluePos;
	olc::vf2d redPos;
	std::unique_ptr<std::list<std::shared_ptr<Entity>>> immortal;
	std::unique_ptr<std::list<std::shared_ptr<Entity>>> mortal;
	
};