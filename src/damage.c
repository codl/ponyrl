#include "damage.h"
#include "roll.h"
#include "creature.h"
#include "item.h"

void critical_hit(struct creature *subject, struct creature *attacker) {
    switch(attacker->wielded->type) {
        case ITEM_HOOF_SPIKES:
           subject->health = subject->health - roll(2,5);
        break;
        default:
        break;
    }
}

void critical_miss(struct creature *subject, struct creature *attacker) {
    switch(attacker->wielded->type) {
        case ITEM_HOOF_SPIKES:
            switch(roll(1,2)) {
                case 1:
                    //the hoof gets stuck! nomove for one turn!
                break;
                case 2:
                    //You stumble onto your muzzle!
                    attacker->health = attacker->health - roll(1,3);
                break;
            }
        break;
        default:
        break;
    }
}

void damage(struct creature *subject, struct creature *attacker) {
    //what weapon?
    switch(attacker->wielded->type) {
        case ITEM_HOOF_SPIKES: /* defined in item.h */
            subject->health = subject->health - roll(1,5); /* how do we get critchance? */
        break;
        default:
            /* how did you get here? */
        break;
    }
}

void hit(struct creature *subject, struct creature *attacker) { /* we roll a d20 to see if we hit. */
    int die = roll(1,20);
    int evade = subject->dex;
    int penalty = skill_check(attacker, attacker->wielded->group); // skill group.

    evade = ((evade - penalty) <= 0)? 1 : (evade - penalty);

    if (evade < die) { /* If you roll higher than the dex you hit. */
        if ((penalty + 1) >= roll(1,20)) { // roll a critical hit check.
            critical_hit(subject, attacker);
        } else {
            damage(subject, attacker); /* he got hit. */
        }
    } else {
        if (((4 - penalty) * 2) >= roll(1,20)) {
            critical_miss(subject, attacker);
        } else {
            //putmessagge you missed
        }
    }
    //TODO Critical failure chance check.
}

