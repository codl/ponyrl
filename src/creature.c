#include "creature.h"
#include "item.h"

/* skill functions */

int skill_check(struct creature *subject, unsigned int type) {
    while(subject->skills != 0) {
        if (subject->skills->skill->type == type) {
            return subject->skills->skill->level;
        }
        subject->skills = subject->skills->next;
    }
    return 0; // if the PC/C does not have this skill in his or her list, this assumes it to be unskilled.
}

//TODO add levelup, add-skill, get skill(if there's a need for such) etc.
