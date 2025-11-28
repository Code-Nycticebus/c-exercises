#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/* OOP with a tagged union.
 * This technique is used in a well defined system.
 * The switch is a bit cumbersome to write but its way safer than the function pointers.
 * The union approach allows Entities to be put into a list next to each other,
 * wastes a bit of memory but its way more cache friendly.
 */

/* -- Header -- */

typedef enum {
    ENTITY_GOBLIN,
    ENTITY_TROLL,
    ENTITY_COUNT,
} EntityType;

typedef struct {
    EntityType type;
    int hp;
    int dmg;
} EntityBase;
// in C11 you should do this assertion.
// static_assert(offsetof(EntityBase, type) == 0, "This depends on type being the first")

typedef union Entity Entity;

typedef struct {
    EntityBase base;
    int ammo;
} EntityGoblin;

void entity_goblin_attack(EntityGoblin *goblin, Entity *target);
void entity_goblin_defend(EntityGoblin *goblin, int dmg);

typedef struct {
    EntityBase base;
    int defense;
} EntityTroll;

void entity_troll_attack(EntityTroll *troll, Entity *target);
void entity_troll_defend(EntityTroll *troll, int dmg);

union Entity {
    EntityType type;
    EntityBase base;
    EntityGoblin goblin;
    EntityTroll troll;
};

void entity_attack(Entity *attack, Entity *target);
void entity_defend(Entity *defend, int dmg);

/* -- Implementation -- */

void entity_attack(Entity *attack, Entity *target) {
    // With the -Wall flag enabled, this warns you from forgetting to add implementations
    switch (attack->type) {
        // taking the address is better than casting for "type safety"
        case ENTITY_GOBLIN: entity_goblin_attack(&attack->goblin, target);
        case ENTITY_TROLL:  entity_troll_attack(&attack->troll, target);
        case ENTITY_COUNT:  assert(false);
    }
}

void entity_defend(Entity *defend, int dmg) {
    // With the -Wall flag enabled, this warns you from forgetting to add implementations
    switch (defend->type) {
        // taking the address is better than casting for "type safety"
        case ENTITY_GOBLIN: entity_goblin_defend(&defend->goblin, dmg);
        case ENTITY_TROLL:  entity_troll_defend(&defend->troll, dmg);
        case ENTITY_COUNT:  assert(false);
    }
}

void entity_goblin_attack(EntityGoblin *goblin, Entity *target) {
    if (goblin->ammo > 0) {
        goblin->ammo -= 1;
        entity_defend(target, goblin->base.dmg);
    }
}

void entity_goblin_defend(EntityGoblin *goblin, int dmg) {
    goblin->base.hp -= dmg;
    if (goblin->base.hp < 0) goblin->base.hp = 0;
}

void entity_troll_attack(EntityTroll *troll, Entity *target) {
    entity_defend(target, troll->base.dmg);
}

void entity_troll_defend(EntityTroll *troll, int dmg) {
    if (troll->defense >= dmg) return;

    troll->base.hp -= dmg - troll->defense;
    if (troll->base.hp < 0) troll->base.hp = 0;
}

/* -- User Code -- */

int main(void) {
    Entity e1 = {
        .goblin = {
            .base = {
                .type = ENTITY_GOBLIN,
                .hp = 10,
                .dmg = 3,
            },
            .ammo = 3,
        },
    };


    Entity e2 = {
        .troll = {
            .base = {
                .type = ENTITY_TROLL,
                .hp = 30,
                .dmg = 8,
            },
            .defense = 3,
        },
    };

    entity_attack(&e2, &e1);
    printf("%d\n", e1.base.hp);
}
