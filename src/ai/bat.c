#include "ai.h"

#include <genesis.h>
#include "audio.h"
#include "player.h"
#include "stage.h"
#include "tables.h"
#include "tsc.h"

// The range is a bit too high so here is my lazy way to fix it
void ai_batVertical_onCreate(Entity *e) {
	e->y += pixel_to_sub(24);
}

// Just up and down gotta go up and down
void ai_batVertical_onUpdate(Entity *e) {
	if(e->state == 0) {
		e->y_speed -= 8;
		if(e->y_speed <= pixel_to_sub(-1)) e->state = 1;
	} else if(e->state == 1) {
		e->y_speed += 8;
		if(e->y_speed >= pixel_to_sub(1)) e->state = 0;
	}
	e->y += e->y_speed;
}
