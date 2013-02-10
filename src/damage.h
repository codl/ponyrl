#ifndef DAMAGE_H
#define DAMAGE_H

#include "_enemy.h"

void critical_hit(npc *subject, npc *attacker);
void critical_miss(npc *subject, npc *attacker);
void damage(npc *subject, npc *attacker);
void hit(npc *subject, npc *attacker);

#endif
