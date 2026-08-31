#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/keycodes.h>
#include <allegro5/system.h>
#include <allegro5/allegro_image.h>

#include <stdexcept>

#include "../include/Display.h"
#include "../include/Mouse.h"
#include "../include/Timer.h"
#include "../include/Keyboard.h"
#include "../include/Renderer.h"
#include "../include/Bullet.h"
#include "../include/Tank.h"

int main() {
	al_init();
	al_init_image_addon();

	if (!al_is_image_addon_initialized()) throw std::runtime_error("Image addon could not be initialized!");

	bool running = true;

	//allegro prefers destruction in reverse order of creation, so this order of RAII constructors matters
	Display display{800, 600};
	Renderer renderer;
	Mouse mouse;
	Timer timer(300);
	Keyboard kb;

	//test bullet
	Tank tank1(100, 100);
	Tank tank2(200, 50);

	Bullet bullet;

	renderer.add(tank1);
	renderer.add(tank2);
	renderer.add(bullet);

	double prev_time = al_get_time();
	int dir = 0;

	while(running) {
		double curr_time = al_get_time();
		double delta = curr_time - prev_time;
		prev_time = curr_time;

		mouse.Update();
		kb.Update();

		if (mouse.GetMouseButtonPressed(0)) {
			bullet.setDirection((++dir) % 4);
		}

		if (kb.GetKeyPressed(ALLEGRO_KEY_UP)) {
			tank1.setDirection(0);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_RIGHT)) {
			tank1.setDirection(1);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_DOWN)) {
			tank1.setDirection(2);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_LEFT)) {
			tank1.setDirection(3);
		}

		if (kb.GetKeyPressed(ALLEGRO_KEY_W)) {
			tank2.setDirection(0);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_D)) {
			tank2.setDirection(1);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_S)) {
			tank2.setDirection(2);
		} else if (kb.GetKeyPressed(ALLEGRO_KEY_A)) {
			tank2.setDirection(3);
		}

		if (kb.GetKeyDown(ALLEGRO_KEY_UP) ||
		kb.GetKeyDown(ALLEGRO_KEY_DOWN) ||
		kb.GetKeyDown(ALLEGRO_KEY_RIGHT) ||
		kb.GetKeyDown(ALLEGRO_KEY_LEFT))
			tank1.move();

		if (kb.GetKeyDown(ALLEGRO_KEY_W) ||
		kb.GetKeyDown(ALLEGRO_KEY_S) ||
		kb.GetKeyDown(ALLEGRO_KEY_D) ||
		kb.GetKeyDown(ALLEGRO_KEY_A))
			tank2.move();

		bullet.move();

		al_clear_to_color(al_map_rgb(0, 0, 0));
		renderer.draw();
		al_flip_display();
	}

	return 0;
}
