#ifndef UI_STRUCTS_H
# define UI_STRUCTS_H

#include "SDLX.h"

typedef struct Button
{
	SDLX_GUIElem elem;
	SDLX_Sprite sprite;
	SDLX_Animator anim;

	int isTrigger;
}				Button;

typedef struct Page
{
	SDLX_Sprite art;
	Button		upgrades[5];

	int 		nUpgrades;
	SDL_bool	isLocked;
}				Page;



#endif
