#pragma once

#include "./Entity.h"
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/color.h>
#include <array>
#include <cstdio>
#include <stdexcept>

#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Bullet : public Entity {
private:
	float damagePerHit = 5.0;
	float x = 0.0, y = 0.0;
	float speed = 1.0;
	int direction = 1;
	ALLEGRO_BITMAP* bitmap;
public:
	Bullet() {
		bitmap = al_load_bitmap("assets/bullet.bmp");
		if (!bitmap) throw std::runtime_error("Bitmap could not be loaded");
	}
	Bullet(const char* path) {
		bitmap = al_load_bitmap(path);
		if (!bitmap) throw std::runtime_error("Bitmap could not be loaded");
	}
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	Bullet(Bullet&&) = delete;
	Bullet& operator=(Bullet&&) = delete;
	~Bullet() {
		al_destroy_bitmap(bitmap);
	}

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
	void setDirection(int dir) {
		if (direction < 0 || direction > 3) return;
		direction = dir;
	}
	//END getters & setters

	std::array<float, 2> getPosition() const override {
		return {x, y};
	}
	ALLEGRO_BITMAP* getBitmap() const override {
		return bitmap;
	}
	void draw() override {
		float sx = 0, sy = 0;
		sx = direction * 32;
		al_draw_scaled_bitmap(bitmap, sx, sy, 32, 32, x, y, 128, 128, 0);
	}

	void move() {
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
	AdvancedBullet(): Bullet("assets/advanced_bullet.bmp") {
		setDamagePerHit(10.0);
		setSpeed(5.0);
	}
};
