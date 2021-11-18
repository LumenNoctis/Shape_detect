# include "rush.h"

void main_levelInit(void *arg)
{
	SDLX_Anim	**a_beam;

	SDL_Texture *t_beam;
	SDL_Texture *t_pause;
	SDL_Texture *t_scroll;
	SDL_Rect scroll;
	SDL_Rect pause_src;
	SDL_Rect pause_dst;
	SDL_Rect beamrect;
	SDL_Rect dst;

	Context *ctx;
	int i;

	ctx = getCtx();

	initSpells();
	initSpellData();


	dst.h = 10;
	dst.w = 0;

	ctx->level.drawing = SDLX_FALSE;

	// init_pause();

	init_enemies();
	init_enemyData();
	ctx->level.area = loadArea(0);
	NextWave(ctx->level.area);
}
