#pragma once

#include <allegro5/events.h>
#include<allegro5/timer.h>

class Timer {
private:
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* timerEq;
	ALLEGRO_EVENT ev;
public:
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	Timer(Timer&& other) noexcept : timer(other.timer) {
		other.timer = nullptr;
		timerEq = al_create_event_queue();
		al_register_event_source(timerEq, al_get_timer_event_source(timer));
		al_start_timer(timer);
	}
	Timer& operator=(Timer&& other) noexcept {
		if (this != &other) {
			timer = other.timer;
			timerEq = other.timerEq;
			other.timer = nullptr;
			other.timerEq = nullptr;
		}

		return *this;
	}
	bool Tick() {
		al_wait_for_event(timerEq, &ev);
		switch (ev.type) {
			case ALLEGRO_EVENT_TIMER:
				return true;
			default:
				return false;
		}
	}
	Timer(double fps) {
		timer = al_create_timer(1 / fps);
		timerEq = al_create_event_queue();
		al_register_event_source(timerEq, al_get_timer_event_source(timer));
		al_start_timer(timer);
	}
	~Timer() {
		al_stop_timer(timer);
		al_destroy_timer(timer);
		al_destroy_event_queue(timerEq);
	}
};
