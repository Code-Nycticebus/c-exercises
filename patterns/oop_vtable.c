#include<stdio.h>

/* OOP with virtual functions.
 * This technique is used when creating an extensible system where the user creates their own classes.
 * Function Pointers are slow. And needing pointers to the structs is not chache friendly, because
 * you can't create a list next to each other.
 */

typedef struct EntityInterface EntityInterface;

// The base class used as a struct header
typedef struct {
    const EntityInterface* interface;
    int hp;
    int dmg;
} EntityBase;

// The vtable for virtual functions.
struct EntityInterface {
    void (*defend)(EntityBase* entity, int dmg);
    void (*attack)(EntityBase* entity, EntityBase* target);
};

void entity_attack(EntityBase *attack, EntityBase *defend) {
    attack->interface->attack(attack, defend);
}

void entity_defend(EntityBase *defend, EntityBase *attack) {
    defend->interface->defend(defend, attack->dmg);
}

/* -- User Code -- */

// Goblin inherits from EntityBase by having the base as the first member
typedef struct {
    EntityBase base;
    int ammo;
} Goblin;

static void goblin_defend(EntityBase* entity, int dmg) {
    (void)dmg;
    entity->hp = 0;
}

static void goblin_attack(EntityBase* entity, EntityBase* target) {
    Goblin *goblin = (Goblin*)entity;
    if (goblin->ammo > 0) {
        goblin->ammo -= 1;
        entity_defend(target, entity);
    }
}

void goblin_init(Goblin *goblin, int speed, int hp, int dmg, int ammo) {
    static const EntityInterface GoblinInterface = {
        .defend=goblin_defend,
        .attack=goblin_attack,
    };
    goblin->base.interface = &GoblinInterface;

    goblin->base.hp = hp;
    goblin->base.dmg = dmg;
    goblin->ammo = ammo;
}

// Troll also inherits from EntityBase by having the base as its first member
typedef struct {
    EntityBase base;
    int def;
} Troll;

static void troll_defend(EntityBase* entity, int dmg) {
    Troll* troll = (Troll*)entity;
    if (dmg < troll->def) {
        return;
    }
    entity->hp -= dmg - troll->def;
}

static void troll_attack(EntityBase* entity, EntityBase* target) {
    entity_defend(target, entity);
}

void troll_init(Troll *troll, int hp, int dmg, int def) {
    static const EntityInterface TrollInterface = {
        .defend=troll_defend,
        .attack=troll_attack,
    };
    troll->base.interface=&TrollInterface;

    troll->base.hp = hp;
    troll->base.dmg = dmp;
    troll->def = def;
}

int main(void) {
    Goblin g1 = {0};
    goblin_init(&g1, 10, 6, 3);

    Troll t1 = {0};
    troll_init(&t1, 30, 6, 5);

    entity_attack((EntityBase*)&g1, (EntityBase*)&t1);
    printf("%d\n", t1.base.hp);
    printf("%d\n", g1.ammo);
}
