#include<stdio.h>
#include<stdint.h>

typedef struct {
	void (*defend)(EntityBase* entity, uint8_t dmg);
	void (*attack)(EntityBase* entity, EntityBase* target);
} EntityInterface;

typedef struct {
	const EntityInterface* interface;
	uint8_t hp;
	uint8_t dmg;
} EntityBase;


/* GOBLIN */
typedef struct {
	EntityBase base;
} Goblin;

static void goblin_defend(EntityBase* entity, uint8_t dmg) {
	(void)dmg;
	entity->hp = 0;
}

static void goblin_attack(EntityBase* entity, EntityBase* target) {
	target->interface->defend(target, entity->dmg);
}

const static EntityInterface GoblinInterface = {
	.defend=goblin_defend,
	.attack=goblin_attack,
};


/* TROLL */
typedef struct {
	EntityBase base;
	uint8_t def;
} Troll;

static void troll_defend(EntityBase* entity, uint8_t dmg) {
	(void)dmg;
	Troll* troll = (Troll*)entity;
	if (dmg < troll->def) {
		return;
	}
	entity->hp -= dmg - troll->def;
}

static void troll_attack(EntityBase* entity, EntityBase* target) {
	target->interface->defend(target, entity->dmg);
}

const static EntityInterface TrollInterface = {
	.defend=troll_defend,
	.attack=troll_attack,
};

/* MAIN */
int main(void) {
	Goblin g1 = {
		.base.interface=&GoblinInterface, 
		.base.hp=10, 
		.base.dmg=6
	};
	Troll t1 = {.base.interface=&TrollInterface, .base.hp=30, .base.dmg=6, .def=5};
	
	g1.base.interface->attack((EntityBase*)&g1, (EntityBase*)&t1);
	printf("%d\n", t1.base.hp);
}
