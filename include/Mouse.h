#pragma once

#include <allegro5/events.h>
#include <allegro5/mouse.h>
#include <print>

class Mouse {
private:
	ALLEGRO_EVENT_QUEUE* mouseEq;
	ALLEGRO_EVENT ev;
	bool buttonsDown[3] = {0};
public:
	Mouse() {
		al_install_mouse();
		mouseEq = al_create_event_queue();
		al_register_event_source(mouseEq, al_get_mouse_event_source());
	}
	Mouse(const Mouse&) = delete;
	Mouse(Mouse&& other): mouseEq(other.mouseEq) {
		al_install_mouse();
		al_register_event_source(mouseEq, al_get_mouse_event_source());

		other.mouseEq = nullptr;
	}
	Mouse& operator=(Mouse&& other) {
		if (this != &other) {
			mouseEq = other.mouseEq;
			other.mouseEq = nullptr;
		}

		return *this;
	}
	void Update() {
		while(al_get_next_event(mouseEq, &ev)) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				unsigned int btnId = ev.mouse.button-1;
				buttonsDown[btnId] = true;
			} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				unsigned int btnId = ev.mouse.button-1;
				buttonsDown[btnId] = false;
			}
		}
	}
	bool GetMouseButtonDown(unsigned int id) {
		return buttonsDown[id];
	}
	bool GetMouseButtonPressed(unsigned int id) {
		return true;
	}
	bool GetMouseButtonReleased(unsigned int id) {
		return true;
	}
	bool GetMouseButtonUp(unsigned int id) {
		return !buttonsDown[id];
	}
};
