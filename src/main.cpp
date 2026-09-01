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
#include "../include/Tank.h"
#include "../include/ObjectPool.h"

void handleTank(Keyboard&, Tank&);

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

	ObjectPool<Bullet> pool(
		PoolConfig<Bullet>{50},
		PoolConfig<AdvancedBullet>{50}
	);

	//test bullet
	Tank tank1(100, 100, "assets/tank01.png");
	Tank tank2(200, 50, "assets/tank02.png");

	renderer.add(tank1);
	renderer.add(tank2);

	double prev_time = al_get_time();
	int dir = 0;

	while(running) {
		double curr_time = al_get_time();
		double delta = curr_time - prev_time;
		prev_time = curr_time;

		mouse.Update();
		kb.Update();

		handleTank(kb, tank1);
		handleTank(kb, tank2);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		renderer.draw();
		al_flip_display();
	}

	return 0;
}

void handleTank(Keyboard& kb, Tank& tank) {
	if (kb.GetKeyPressed(ALLEGRO_KEY_UP)) {
		tank.setDirection(0);
	} else if (kb.GetKeyPressed(ALLEGRO_KEY_RIGHT)) {
		tank.setDirection(1);
	} else if (kb.GetKeyPressed(ALLEGRO_KEY_DOWN)) {
		tank.setDirection(2);
	} else if (kb.GetKeyPressed(ALLEGRO_KEY_LEFT)) {
		tank.setDirection(3);
	}
	if (kb.GetKeyDown(ALLEGRO_KEY_UP) ||
	kb.GetKeyDown(ALLEGRO_KEY_DOWN) ||
	kb.GetKeyDown(ALLEGRO_KEY_RIGHT) ||
	kb.GetKeyDown(ALLEGRO_KEY_LEFT))
		tank.move();
}
