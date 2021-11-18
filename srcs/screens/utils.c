#include "rush.h"

void StopGame(Context *ctx)
{
	int i;

	i = 0;
	while (i < 100)
	{
		ctx->level.enemies->animator.active = SDLX_FALSE;
		++i;
	}
	i = 0;
	while (i < 10)
	{
		// ctx->player.active[i].c_anim.active = SDLX_FALSE;
		ctx->player.active[i].p_anim.active = SDLX_FALSE;
		i++;
	}
	ctx->player.active->c_anim.active = SDLX_FALSE;
}

void ResumeGame(Context *ctx)
{
	int i;

	i = 0;
	while (i < 100)
	{
		ctx->level.enemies->animator.active = SDLX_TRUE;
		++i;
	}
	i = 0;
	while (i < 10)
	{
		// ctx->player.active[i].c_anim.active = SDLX_FALSE;
		ctx->player.active[i].p_anim.active = SDLX_TRUE;
		i++;
	}
	ctx->player.active->c_anim.active = SDLX_TRUE;
}

void CaptureScreen(SDL_Texture *target)
{

}

void ResetLevel()
{
	Coontex *ctx;

	ctx = getCtx();
	StopGame(ctx);
	ctx->Player.current = NULL;
	ctx->Player.hp = ctx->Player.maxHP;
	ctx->Player.mana = ctx->Player.maxMana;
	ctx->lvl = 0;
}



