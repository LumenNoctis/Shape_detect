#ifndef RUSH_H
# define RUSH_H

# include "core_structs.h"
# include "buttons.h"
# include "enemies.h"
# include "spells.h"

# define STARTX 230
# define STARTY 769
# define FBALL 20616
# define NTYPES 6


static int ctxTrue = SDLX_TRUE;
static int ctxFalse = SDLX_FALSE;
static Spell NoSpell;

static int const weaknessTable [NTYPES][NTYPES] = {
	{10, 20, 10,  5, 10, 10 }, //FIRE
	{ 5, 10, 20, 10, 10, 10 }, //ICE
	{10,  5, 10, 20, 10, 10 }, //EARTH
	{20, 10,  5, 10, 10, 10 }, //WATER

	{10, 10, 10, 10, 10, 20 }, //LIGHT
	{10, 10, 10, 10, 20, 10 }, //SHADOW
};

// Ref for scroll UI so no need to allocate


Context *getCtx(void);

Context *init_game(void);
void	main_menuInit(void *args);
void	main_levelInit(void *args);
void	test_levelInit(void *args);

void	main_menuCleanup(void *arg);
void	main_levelCleanup(void *arg);
void	test_levelCleanup(void *arg);

void	main_menu(void *args);
void	main_level(void *arg);
void	test_level(void *args);

int		ReadyCheck(Spell *spell);
int		GetSpell(void);
void	DrawSpell(void);
void	CastSpell(int id);
void	ActivateSpell(Spell *spell);
void	CopySpell(Spell *src, Spell *dst);

void	renderSprites(void);
void	flushSprites(void);


void	init_pause(SDL_Texture *pauseTex, Context *ctx);


void ResumeGame(Context *ctx);
void StopGame(Context *ctx);
void ResetLevel();

// void	CollisionCheck(Enemy *enemies, int nenemies, Spell *spells, int nspells);

#endif
