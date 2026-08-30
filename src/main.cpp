#include <allegro5/display.h>
#include <allegro5/keycodes.h>
#include <allegro5/system.h>
#include <allegro5/allegro_image.h>

#include <cstdio>
#include <print>

#include "../include/Display.h"
#include "../include/Mouse.h"
#include "../include/Timer.h"
#include "../include/Keyboard.h"
#include "../include/Renderer.h"
#include "../include/Bullet.h"

int main() {
	al_init();
	al_init_image_addon();

	bool running = true;

	//allegro prefers destruction in reverse order of creation, so this order of RAII constructors matters
	Display display{800, 600};
	Renderer renderer;
	Mouse mouse;
	Timer timer(300);
	Keyboard kb;

	//test bullet
	Bullet bullet;

	renderer.add(bullet);
	renderer.draw();

	al_flip_display();

	double prev_time = al_get_time();

	while(running) {
		double curr_time = al_get_time();
		double delta = curr_time - prev_time;
		prev_time = curr_time;

		mouse.Update();
		kb.Update();

		if (mouse.GetMouseButtonPressed(0)) {
			std::println("Left mouse button pressed!");
			std::fflush(stdout);
		}

		if (kb.GetKeyPressed(ALLEGRO_KEY_S)) {
			std::println("Key S pressed!");
			std::fflush(stdout);
		} else if (kb.GetKeyReleased(ALLEGRO_KEY_S)) {
			std::println("Key S released!");
			std::fflush(stdout);
		}
	}

	return 0;
}
