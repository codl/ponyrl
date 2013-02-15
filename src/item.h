#ifndef ITEM_H
#define ITEM_H

/* ITEM TYPES */
#define ITEM_HOOF_SPIKES 0 // w_example_spike

#define ITEM_LENGTH 1 // 0-1

/* GROUP NAMES */
#define WEAPON_HOOF_MELEE 0 // is also the skill number. A PC/C's skill with this group.

#define GROUP_LENGTH 1

struct item {
    unsigned int type :ITEM_LENGTH;
    unsigned int group :GROUP_LENGTH; // group length defined as types are added and defined.
    /* things */
};

struct itemlist {
    struct item* item;
    struct itemlist* next;
};

#endif
