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
#define BULLET_SCALE_FACTOR 2
#define BULLET_WIDTH 32 * BULLET_SCALE_FACTOR
#define BULLET_HEIGHT 32 * BULLET_SCALE_FACTOR

class Bullet : public Entity {
private:
	float damagePerHit = 5.0;
	float x = 0.0, y = 0.0;
	float speed = 1.0;
	int direction = 1;
	ALLEGRO_BITMAP* bitmap;
public:
	Bullet() {
		bitmap = al_load_bitmap("assets/bullet.png");
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
		if (dir < 0 || dir > 3) return;
		direction = dir;
	}
	//END getters & setters

	void draw() override {
		float sx = 0, sy = 0;
		sx = direction * 32;
		al_draw_scaled_bitmap(bitmap, sx, sy, 32, 32, x, y, BULLET_WIDTH, BULLET_HEIGHT, 0);
	}

	void move() {
		// 0123 - TRBL
		
		int halfWidth = BULLET_WIDTH / 2;
		int halfHeight = BULLET_HEIGHT / 2;

		switch (direction) {
			case 0: // Top
				y -= speed;
				if (y < -halfHeight)
					y = SCREEN_HEIGHT - halfHeight;
				break;
			case 1: // Right
				x += speed;
				if (x + halfWidth > SCREEN_WIDTH)
					x = halfWidth;
				break;
			case 2: // Bottom
				y += speed;
				if (y + halfHeight > SCREEN_HEIGHT)
					y = halfHeight;
				break;
			case 3: // Left
				x -= speed;
				if (x < -halfWidth)
					x = SCREEN_WIDTH - halfWidth;
				break;
			default:
				throw std::runtime_error("Wrong direction!");
		}
	}
};

class AdvancedBullet : public Bullet {
	AdvancedBullet(): Bullet("assets/advanced_bullet.png") {
		setDamagePerHit(10.0);
		setSpeed(5.0);
	}
};
