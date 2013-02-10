#ifndef _ENEMY_H
#define _ENEMY_H

typedef struct weapon {
    int id;
} weapon;

typedef struct npc {
    int health;
    int x, y;
    int dex;
    weapon *equipped;
} npc;

#endif
