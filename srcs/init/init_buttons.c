# include "rush.h"

void init_buttons()
{
	SDL_texture *tex;

	tex = SDLX_LoadTexture("Assets/UI/Buttons.png", SDLX_DisplayGet())

	// SDLX_SpriteCreate(&ctx->starMenu.Start.sprite,tex,  );
	// SDLX_AnimatorCreate

	SDLX_GUIElem_Create(&ctx->pause.Resume.elem, 	&ctx->pause.Resume.sprite, 		"Play" ,		&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &UnpauseGame);
	SDLX_GUIElem_Create(&ctx->pause.SpellBook.elem, &ctx->pause.SpellBook.sprite,	"SpellBook",	&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	SDLX_GUIElem_Create(&ctx->pause.Home.elem,		&ctx->pause.Home.sprite,		"Home" ,		&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);

	ctx->pause.Resume.elem.active = SDLX_FALSE;
	ctx->pause.SpellBook.elem.active = SDLX_FALSE;
	ctx->pause.Home.elem.active = SDLX_FALSE;
}

