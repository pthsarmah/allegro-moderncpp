#include <allegro5/system.h>
#include <print>
#include "../include/Display.h"
#include "../include/Mouse.h"
#include "../include/Timer.h"

int main() {
	al_init();

	bool running = true;

	//allegro prefers destruction in reverse order of creation, so this order of RAII constructors matters
	Display display{800, 600};
	Mouse mouse;
	Timer timer(300);

	double prev_time = al_get_time();

	while(running) {
		double curr_time = al_get_time();
		double delta = curr_time - prev_time;
		prev_time = curr_time;

		mouse.Update();

		if (timer.Tick()) {
			if (mouse.GetMouseButtonPressed(0))
				std::print("{}", "Left mouse button pressed!");
			else if (mouse.GetMouseButtonDown(1))
				std::print("{}", "Right mouse button pressed!");
		}
	}

	return 0;
}
