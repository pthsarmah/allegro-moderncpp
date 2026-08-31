#pragma once

#include <allegro5/bitmap.h>
#include <array>
class Entity {
public:
	virtual void draw() = 0;
	virtual ~Entity() = default;
};
