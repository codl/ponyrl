#include "creature.h"
#include "item.h"

/* skill functions */

int skill_check(struct creature *subject, unsigned int type) {
    struct skill_list* list = subject->skills;
    while(list != 0) {
        if (list->skill->type == type) {
            return list->skill->level;
        }
        list = list->next;
    }
    return 0; // if the PC/C does not have this skill in his or her list, this assumes it to be unskilled.
}

//TODO add levelup, add-skill, get skill(if there's a need for such) etc.
