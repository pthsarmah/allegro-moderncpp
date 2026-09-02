#pragma once

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_io.h>
#include <memory>
#include <stdexcept>

struct BitmapDeleter {
	void operator()(ALLEGRO_BITMAP* b) const { al_destroy_bitmap(b); }
};
using BitmapPtr = std::unique_ptr<ALLEGRO_BITMAP, BitmapDeleter>;

inline BitmapPtr loadBitmap(const char* path) {
	BitmapPtr bmp{al_load_bitmap(path)};
	if (!bmp) throw std::runtime_error(std::string("Bitmap could not be loaded: ") + path);
	return bmp;
}
