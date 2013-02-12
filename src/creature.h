#ifndef CREATURE_H
#define CREATURE_H

#define CREA_EARTH_PONY 0
#define CREA_UNICORN 1
#define CREA_PEGASUS 2
#define CREA_LENGTH 2 // 0-3

struct creature{
    unsigned int type :CREA_LENGTH;
    int health;
    int dex; // str, con, lck... ? do they need to be signed? (can they be negative?)
    int x, y, ele;
    struct itemlist* inv;
    struct item* wielded; // Vivix: Is this okay?
    // ??? equipped;   maybe another itemlist that is a subset of inv?
    // int turn_counter;
};

// TODO add skill list, and skill check function.

#endif
