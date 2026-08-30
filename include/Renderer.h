#pragma once

#include "./Entity.h"
#include <vector>

class Renderer {
private:
	std::vector<Entity*> entities;
public:
	void add(Entity& e) {
		entities.push_back(&e);
	}
	void draw() {
		for (Entity*& et : entities) {
			et->draw();
		}
	}
};
