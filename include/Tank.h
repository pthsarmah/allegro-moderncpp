#pragma once

#include "./Bullet.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/base.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/color.h>
#include <array>
#include <stdexcept>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TANK_SCALE_FACTOR 2
#define TANK_WIDTH 32 * TANK_SCALE_FACTOR
#define TANK_HEIGHT 32 * TANK_SCALE_FACTOR

class Tank : public Entity {
private:
	float health = 100.0;
	float x, y = 0.0; //these are the CENTER coords not top left
	float speed = 5.0;
	ALLEGRO_BITMAP* bitmap;
	int direction = 0;
public:
	Tank(float x, float y, const char* path = "assets/tank01.png"): x(x), y(y) {
		bitmap = al_load_bitmap(path);
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
		al_draw_scaled_rotated_bitmap(bitmap, 15, 15, x, y, TANK_SCALE_FACTOR, TANK_SCALE_FACTOR, direction * ALLEGRO_PI / 2, 0);
	}

	void setDirectionInputMappings() {

	}

	void move() {
		// 0123 - TRBL
		
		int halfWidth = TANK_WIDTH / 2;
		int halfHeight = TANK_HEIGHT / 2;

		switch (direction) {
			case 0: // Top
				y -= speed;
				if (y < halfHeight)
					y = halfHeight;
				break;
			case 1: // Right
				x += speed;
				if (x + halfWidth > SCREEN_WIDTH)
					x = SCREEN_WIDTH - halfWidth;
				break;
			case 2: // Bottom
				y += speed;
				if (y + halfHeight > SCREEN_HEIGHT)
					y = SCREEN_HEIGHT - halfHeight;
				break;
			case 3: // Left
				x -= speed;
				if (x < halfWidth)
					x = halfWidth;
				break;
			default:
				throw std::runtime_error("Wrong direction!");
		}
	}

	void shoot() {
		float sx = x, sy = y;
		switch (direction) {
			case 0:
				sy = y - 20;
				break;
			case 1:
				sx = x + 20;
				break;
			case 2:
				sy = y + 20;
				break;
			case 3:
				sy = y - 20;
				break;
		}
	}
};
