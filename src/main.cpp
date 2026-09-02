#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/keycodes.h>
#include <allegro5/system.h>
#include <allegro5/allegro_image.h>

#include <array>
#include <stdexcept>

#include "../include/Display.h"
#include "../include/Mouse.h"
#include "../include/Timer.h"
#include "../include/Keyboard.h"
#include "../include/Renderer.h"
#include "../include/Tank.h"

#include "../include/ObjectPool.h"

void handleTank(Keyboard&, Tank&, std::array<int, 4>&&);

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
	Tank tank1(100, 100, "assets/tank01.png");
	Tank tank2(200, 50, "assets/tank02.png");

	ObjectPool<Bullet> pool(
		PoolConfig<Bullet>{50},
		PoolConfig<AdvancedBullet>{50}
	);

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

		tank1.handleMovement(kb, std::array<int, 4>{
			ALLEGRO_KEY_W,
			ALLEGRO_KEY_D,
			ALLEGRO_KEY_S,
			ALLEGRO_KEY_A
		});
		tank1.handleShoot(kb, ALLEGRO_KEY_SPACE, renderer, pool);

		tank2.handleMovement(kb, std::array<int, 4>{
			ALLEGRO_KEY_UP,
			ALLEGRO_KEY_RIGHT,
			ALLEGRO_KEY_DOWN,
			ALLEGRO_KEY_LEFT
		});
		tank2.handleShoot(kb, ALLEGRO_KEY_RSHIFT, renderer, pool);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		renderer.draw();
		al_flip_display();
	}

	return 0;
}
