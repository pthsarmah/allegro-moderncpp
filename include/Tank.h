#pragma once

#include "./Bullet.h"

#include <allegro5/base.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
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
	ALLEGRO_BITMAP* bitmap;
	int direction = 0;
public:
	Tank(float x, float y): x(x), y(y) {
		bitmap = al_load_bitmap("assets/tank01.bmp");
	}
	Tank(const Tank&) = delete;
	Tank& operator=(const Tank&) = delete;
	Tank(Tank&&) = delete;
	~Tank() {
		al_destroy_bitmap(bitmap);
	}

	//getters & setters
	void setDirection(int dir) {
		if (dir < 0 || dir > 4) return;
		direction = dir;
	}
	//end getters & setters

	void draw() override {
		al_draw_scaled_rotated_bitmap(bitmap, 15, 15, x+100, y+100, 2, 2, direction * ALLEGRO_PI / 2, 0);
	}

	void move() {
		// 0123 - TRBL
		switch (direction) {
			case 0:
				if (y < 0) { y = SCREEN_HEIGHT-1; break; }
				if (y > 0) y -= speed;
				break;
			case 1:
				if (x >= SCREEN_WIDTH) { x = 0; break; }
				if (x < SCREEN_WIDTH) x += speed;
				break;
			case 2:
				if (y >= SCREEN_HEIGHT) { y = 0; break; }
				if (y < SCREEN_HEIGHT) y += speed;
				break;
			case 3:
				if (x < 0) { x = SCREEN_WIDTH-1; break; }
				if (x > 0) x -= speed;
				break;
			default:
			std::runtime_error("Wrong direction!");
		}
	}
};
