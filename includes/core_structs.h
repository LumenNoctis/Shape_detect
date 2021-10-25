#ifndef CORE_STRUCTS_H
# define CORE_STRUCTS_H

# include "structs/level_structs.h"
# include "structs/ui_structs.h"

typedef struct PauseMenu
{
	Button Home;
	Button Shop;
	Button Resume;
	Button SpellBook;
	SDL_Texture *bg;

	void *data;
}				PauseMenu;

typedef struct ShopMenu
{
	SDLX_Sprite reroll;
	Button Shop;
	Button Resume;
	Button SpellBook;
	Button Home;
	SDL_Texture *bg;

	void *data;
}				ShopMenu;

typedef struct SpellBook
{
	Page pages[10];

	int npages;
	int pageIdx;
	Button back;
	SDL_Texture *bg;

	void *data;
}				SpellBook;

typedef struct MainLevel
{
	Button Pause;
	Button Shop;

	Area *area;

	int drawing;
	int state;
}			MainLevel;

typedef struct Context
{
	Spell 		spells[20];
	Enemy		enemy_data[50];
	PlayerData	player;

	MainLevel level;
	SpellBook book;
	ShopMenu shop;
	PauseMenu pause;

	int lvl;
	int overlay;
}			Context;

#endif
