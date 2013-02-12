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
    int penalty = 0;
    
    switch(attacker->wielded->group) {
        case WEAPON_HOOF_MELEE:
            // check for our required skill.
            //penalty = skill_level(SKILL_HOOF_MELEE); // TODO add and implement this and critchance.
        break;
    }

    if ((subject->dex + penalty) < die) { /* If you roll higher than the dex you hit. */
        damage(subject, attacker); /* he got hit. */
    } else if (die == 1) { /* this value must be modified by critchance. 1=0.5% */
        critical_miss(subject, attacker);
    } else {
        //missed
    }
}

