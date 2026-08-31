#pragma once

#include <allegro5/events.h>
#include <allegro5/mouse.h>
#include <print>

class Mouse {
private:
	ALLEGRO_EVENT_QUEUE* mouseEq;
	ALLEGRO_EVENT ev;
	bool buttonsDown[3] = {0};

	ALLEGRO_MOUSE_STATE currentState{};
	ALLEGRO_MOUSE_STATE previousState{};
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
	~Mouse() {
		al_destroy_event_queue(mouseEq);
		al_uninstall_mouse();
	}
	void Update() {

		previousState = currentState;
		al_get_mouse_state(&currentState);

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
		bool current = currentState.buttons & (1 << id);
		bool previous = previousState.buttons & (1 << id);
		return current && !previous;
	}
	bool GetMouseButtonReleased(unsigned int id) {
		bool current = currentState.buttons & (1 << id);
		bool previous = previousState.buttons & (1 << id);
		return !current && previous;
	}
	bool GetMouseButtonUp(unsigned int id) {
		return !buttonsDown[id];
	}
};
