#pragma once

#include "./Entity.h"
#include <array>
#include <stdexcept>
#include <allegro5/bitmap.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Bullet : public Entity {
private:
	float damagePerHit = 5.0;
	float x, y = 0.0;
	float speed = 1.0;
	ALLEGRO_BITMAP* bitmap;
public:
	Bullet() {}
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	Bullet(Bullet&&) = delete;
	Bullet& operator=(Bullet&&) = delete;

	//getters & setters
	void setDamagePerHit(float amount) {
		if (amount <= 0.0) return;
		damagePerHit = amount;
	}
	float getDamagePerHit() {
		return damagePerHit;
	}
	void setSpeed(float amount) {
		if (amount <= 0.0) return;
		speed = amount;
	}
	float getSpeed() {
		return speed;
	}
	//END getters & setters

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

class AdvancedBullet : public Bullet {
	AdvancedBullet() {
		setDamagePerHit(10.0);
		setSpeed(5.0);
	}
};
