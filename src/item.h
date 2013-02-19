#ifndef ITEM_H
#define ITEM_H

/* ITEM TYPES */
#define ITEM_HOOF_SPIKES 0 // w_example_spike

#define ITEM_LENGTH 1 // 0-1

struct item {
    unsigned int type :ITEM_LENGTH;
    /* things */
};

struct itemlist {
    struct item* item;
    struct itemlist* next;
};

int weapon_skill(unsigned int weapon_type);

#endif
