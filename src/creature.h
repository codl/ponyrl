#ifndef CREATURE_H
#define CREATURE_H

#define CREA_EARTH_PONY 0
#define CREA_UNICORN 1
#define CREA_PEGASUS 2
#define CREA_LENGTH 2 // 0-3

struct creature{
    unsigned int type :CREA_LENGTH;
    int health;
//  int dex; // str, con, lck... ? do they need to be signed? (can they be negative?)
    unsigned int str, end, dex, wis, intl, chr : 8; // 1-8
    int x, y, ele;
    struct itemlist* inv;
    struct item* wielded; // Vivix: Is this okay?
    struct skill_list* skills; // _ because lllist is odd.
    // ??? equipped;   maybe another itemlist that is a subset of inv?
    // int turn_counter;
};

/* skill section */

#define SKILL_HOOF_MELEE 0 //NB: This is grouped with the GROUP list in item.h, do not know if they can be merged fully.

#define SKILL_LENGTH 1

struct skill {
    unsigned int type :SKILL_LENGTH;
    unsigned int level :3; // 0 1 2 3, unskilled decent skilled master
    /* additional stuff */
};

struct skill_list {
    struct skill* skill;
    struct skill_list* next;
};

int skill_check(struct creature *subject, unsigned int type); /* returns skill level of a named skill from subject. */

#endif
