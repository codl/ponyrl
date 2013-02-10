#include "damage.h"
#include "roll.h"
#include "_enemy.h"
#include "items.h"

void critical_hit(npc *subject, npc *attacker) {
    switch(attacker->equipped->id) {
        case HOOF_SPIKES:
           subject->health = subject->health - roll(2,5);
        break;
        default:
        break;
    }
}

void critical_miss(npc *subject, npc *attacker) {
    switch(attacker->equipped->id) {
        case HOOF_SPIKES:
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

void damage(npc *subject, npc *attacker) {
    //what weapon?
    switch(attacker->equipped->id) {
        case HOOF_SPIKES: /* defined in items.h */
            subject->health = subject->health - roll(1,5); /* how do we get critchance? */
        break;
        default:
            /* how did you get here? */
        break;
    }
}

void hit(npc *subject, npc *attacker) { /* we roll a d20 to see if we hit. */
    /* I don't know */
    if (subject->dex < roll(1,20)) { /* you need to get this value from whomever got hit. */
        damage(subject, attacker); /* he got hit. */
    } else if (roll(1,20) == 1) { /* this value must be modified by critchance. 1=0.5% */
        critical_miss(subject, attacker);
    } else {
        //missed
    }
}
