#ifndef SPELLS_H
# define SPELLS_H

#include "data_structs.h"

int 	initSpells();
int 	initSpellData(void);
int 	Fireball(Spell *spell);
int 	NoSpellFn(Spell *spell);


SDL_bool spell_collide(SDLX_Collider *self, SDLX_Collider *other);
void	fireball_react(SDLX_Collider *self, SDLX_Collider *other);

#endif
