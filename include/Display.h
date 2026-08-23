#pragma once

#include<allegro5/allegro5.h>
#include <allegro5/display.h>

class Display {
private:
	ALLEGRO_DISPLAY* display;
public:
	Display(int width, int height) {
		display = al_create_display(width, height);
	}

	//raw content provider
	ALLEGRO_DISPLAY* get() {
		return display;
	}

	//no copy stuff
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;

	//only move stuff
	Display(Display&& other): display(other.display) { other.display = nullptr; }
	Display& operator=(Display&& other) noexcept {
		if (this == &other)
			return *this;

		display = other.display;
		other.display = nullptr;
		return *this;
	}

	~Display() {
		if (display)
			al_destroy_display(display);
	}
};
