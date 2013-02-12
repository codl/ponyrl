#ifndef DAMAGE_H
#define DAMAGE_H

#include "creature.h"

void critical_hit(struct creature *subject, struct creature *attacker);
void critical_miss(struct creature *subject, struct creature *attacker);
void damage(struct creature *subject, struct creature *attacker);
void hit(struct creature *subject, struct creature *attacker);

#endif
