# include "rush.h"

int MenuEnterHover(SDLX_GUIElem *elem)
{
	int cursor;
	Context *ctx;

	cursor = *(int *)elem->data;
	ctx = getCtx();
	// ctx->sprites[cursor].dst->h = 64;
	// ctx->sprites[cursor].dst->w = 64;
	// ctx->sprites[cursor].dst->y = elem->sprite->dst->y;
	// ctx->sprites[cursor].dst->x = elem->sprite->dst->x - 98;
	// SDL_Log("Cursor %d (%d,%d) w %d, h %d\n",
	// ctx->sprites[cursor].dst.x,
	// ctx->sprites[cursor].dst.y,
	// ctx->sprites[cursor].dst.w,
	// ctx->sprites[cursor].dst.h
	// );

	return 0;
}

int MenuExitHover(SDLX_GUIElem *elem)
{
	int cursor;
	Context *ctx;

	cursor = *(int *)elem->data;
	ctx = getCtx();
	// ctx->sprites[cursor].dst->w = 0;

	return 0;
}

int StartClick(SDLX_GUIElem *elem)
{
	SDLX_LevelManagerSwitch(1, NULL);
	SDL_Log("HIT start\n");

	return 0;
}

int ExitClick(SDLX_GUIElem *elem)
{
	SDLX_LevelManagerSwitch(0, NULL);
	SDL_Log("HIT exit\n");

	return 0;
}

