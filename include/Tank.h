#pragma once

#include "./Bullet.h"

#include <array>
#include <stdexcept>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Tank : public Entity {
private:
	float health = 100.0;
	float x, y = 0.0;
	float speed = 5.0;
	Bullet bullet;
public:
	Tank(float x, float y): x(x), y(y) {}
	Tank(const Tank&) = delete;
	Tank& operator=(const Tank&) = delete;
	Tank(Tank&&) = delete;

	std::array<float, 2> getPosition() const override {
		return {x, y};
	}

	void move(int direction) {
		// 0123 - TRBL
		switch (direction) {
			case 0:
				if (y > 0) y -= speed;
				break;
			case 1:
				if (x < SCREEN_WIDTH) x += speed;
				break;
			case 2:
				if (y < SCREEN_HEIGHT) y += speed;
				break;
			case 3:
				if (x > 0) x -= speed;
				break;
			default:
			std::runtime_error("Wrong direction!");
		}
	}
};
