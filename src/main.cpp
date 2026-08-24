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

		if (mouse.GetMouseButtonPressed(0)) {
			std::println("Left mouse button pressed!");
			std::fflush(stdout);
		}

		if (timer.Tick()) {

		}
	}

	return 0;
}
