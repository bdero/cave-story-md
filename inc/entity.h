#ifndef INC_ENTITY_H_
#define INC_ENTITY_H_

#include "common.h"

#define FILTER_NONE 0
#define FILTER_ID 1
#define FILTER_EVENT 2
#define FILTER_TYPE 3
#define FILTER_ALL 4

typedef struct Entity {
	// We linked list now
	struct Entity *next;
	u16 id; // Entity ID (from the stage PXE, or when created by a TSC script)
	u16 event; // Event # to run when triggered
	u16 type; // NPC type - index of npc_info in tables.c (npc.tbl in original game)
	u16 flags; // NPC flags - see tables.h for what the flags are
	// This is assumed to be an array of type u16[2], or at least next to each other
	// in memory. Index 0 is current joy state, 1 is previous frame's state
	u16 *controller;
	// Combat
	u16 health; // If this is an enemy it will die when health reaches 0
	u8 attack; // Damage inflicted on player when colliding
	u8 experience; // How much weapon energy/exp is dropped when killed
	u8 hurtSound; // Sound ID that plays when the entity is hurt
	u8 deathSound; // Sound ID that plays when the entity dies
	u8 deathSmoke;
	// For physics - All this stuff is measured in sub-pixel units
	s32 x; s32 y;
	s32 x_next; s32 y_next; // What x and y will be next frame
	s16 x_speed; s16 y_speed;
	//s16 accel; s16 max_speed;
	// True when on the ground, enables jumping and on-ground collision is a bit
	// different (have to stick to downward slopes, etc)
	bool grounded;
	// When pressing the jump button, this is set to the "max jump time" and
	// decrements each frame until either it reaches zero, or the button is released
	// It gives control over how high the player jumps
	u8 jump_time;
	// Collidable area, for both physics and combat
	// This is measured in pixels
	bounding_box hit_box;
	// Sprite ID assigned to this entity, or SPRITE_NONE
	u8 sprite;
	// Area where sprite is displayed relative to the center
	// Like hit_box this is also pixels
	bounding_box display_box;
	u8 anim; // Current animation of the sprite being displayed
	// Used to generate damage strings
	s8 damage_value;
	s8 damage_time;
} Entity; // 54 bytes

// First element of the "active" list and the "inactive" list
Entity *entityList, *inactiveList;

// Deletes entities based on a criteria
void entities_clear(u8 criteria, u16 value);
// Counts the number of active entities
u16 entities_count();
// Per frame update for entities
void entities_update();
// This one is called by the camera when it moves
void entities_update_inactive();

Entity *entity_create(u16 x, u16 y, u16 id, u16 event, u16 type, u16 flags);
Entity *entity_find_by_id(u16 id);
void entity_update_movement(Entity *e);
void entity_update_walk(Entity *e);
void entity_update_jump(Entity *e);
void entity_update_float(Entity *e);
void entity_update_collision(Entity *e);
bool entity_overlapping(Entity *a, Entity *b);

#endif // INC_ENTITY_H_