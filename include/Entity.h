#pragma once

#include <allegro5/bitmap.h>
#include <array>
class Entity {
private:
	bool isSpriteMap = false;
public:
	void setIsSpriteMap(bool value) {
		isSpriteMap = value;
	}
	bool getIsSpriteMap() {
		return isSpriteMap;
	}
	virtual void draw() = 0;
	virtual std::array<float, 2> getPosition() const = 0;
	virtual ALLEGRO_BITMAP* getBitmap() const = 0;
	virtual ~Entity() = default;
};
