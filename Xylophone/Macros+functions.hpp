#pragma once

#include <cmath>
#include <cstdint>

#include "olcPixelGameEngine.h"

#include "Entity.hpp"

// Directional macros for vectors
#define NORTH(x)	(-x)
#define SOUTH(x)	(abs(x))
#define WEST(x)		(-x)
#define EAST(x)		(abs(x))

template <class T> inline int8_t signof(const T &v)
{
	return signbit(v) ? -1 : 1;
}

