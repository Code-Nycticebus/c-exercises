#pragma once
#include<stdint.h>

typedef struct EntityInterface EntityInterface;

typedef struct {
	const EntityInterface* interface;
	uint8_t hp;
	uint8_t dmg;
} EntityBase;

struct EntityInterface {
	void (*defend)(EntityBase* entity, uint8_t dmg);
	void (*attack)(EntityBase* entity, EntityBase* target);
};

