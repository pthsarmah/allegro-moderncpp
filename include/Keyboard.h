#pragma once

#include <allegro5/events.h>
#include<allegro5/keyboard.h>
#include <allegro5/keycodes.h>

class Keyboard {
	ALLEGRO_EVENT_QUEUE* keyboardEq;
	ALLEGRO_KEYBOARD_STATE currentState, previousState;
	ALLEGRO_EVENT ev;	
	bool keysDown[ALLEGRO_KEY_MAX] = {0};
public:
	Keyboard() {
		al_install_keyboard();
		keyboardEq = al_create_event_queue();
		al_register_event_source(keyboardEq, al_get_keyboard_event_source());
	}
	Keyboard(const Keyboard&) = delete;
	Keyboard(Keyboard&& other): keyboardEq(other.keyboardEq) {
		al_install_keyboard();
		al_register_event_source(keyboardEq, al_get_keyboard_event_source());

		other.keyboardEq = nullptr;
	}
	Keyboard& operator=(Keyboard&& other) {
		if (this != &other) {
			keyboardEq = other.keyboardEq;
			other.keyboardEq = nullptr;
		}

		return *this;
	}
	~Keyboard() {
		al_destroy_event_queue(keyboardEq);
		al_uninstall_keyboard();
	}
	void Update() {

		previousState = currentState;
		al_get_keyboard_state(&currentState);

		while(al_get_next_event(keyboardEq, &ev)) {
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				unsigned int btnId = ev.keyboard.keycode;
				keysDown[btnId] = true;
			} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				unsigned int btnId = ev.keyboard.keycode;
				keysDown[btnId] = false;
			}
		}
	}
	bool GetKeyDown(int keycode) {
		return keysDown[keycode];
	}
	bool GetKeyPressed(int keycode) {
		bool current = al_key_down(&currentState, keycode);
		bool previous = al_key_down(&previousState, keycode);
		return current && !previous;
	}
	bool GetKeyUp(unsigned int keycode) {
		return keysDown[keycode];
	}
	bool GetKeyReleased(int keycode) {
		bool current = al_key_down(&currentState, keycode);
		bool previous = al_key_down(&previousState, keycode);
		return !current && previous;
	}
};
