#include "rush.h"


int initSpells(void)
{
	Context		*ctx;
	SDL_Rect 	dst;
	int i;

	static int wasInit;

	i = 0;
	ctx = getCtx();


	if (!wasInit)
	{
		dst.h = 128;
		dst.w = 128;
		dst.x = STARTX;
		dst.y = STARTY;
		while (i < 10)
		{
			SDLX_SpriteCreate(&ctx->player.active[i].cast, NULL, NULL, &dst);
			SDLX_SpriteCreate(&ctx->player.active[i].projectile, NULL, NULL, &dst);
			SDLX_AnimatorCreate(&(ctx->player.active[i].c_anim), NULL, 0, &ctx->player.active[i].cast);
			SDLX_AnimatorCreate(&(ctx->player.active[i].p_anim), NULL, 0, &ctx->player.active[i].projectile);
			ctx->player.active[i].p_anim.active = SDLX_FALSE;
			ctx->player.active[i].c_anim.active = SDLX_FALSE;
			SDLX_ColliderCreate(L_SPELL | L_ENEMY, 0, ctx->player.active[i].projectile.dst,
								&ctx->player.active[i].collider, spell_collide, NULL, &ctx->player.active[i].info);
			i++;
		}
		ctx->player.current = &NoSpell;
		wasInit = 1;
	}
	return wasInit;
}

int initSpellData(void)
{
	Context		*ctx;
	SDL_Rect 	dst;
	SDL_Texture *t_Fireball;
	SDLX_Anim	**a_Fireball;

	static int wasInit;


	if (!wasInit)
	{
		ctx = getCtx();

		dst.h =  98 * 2;
		dst.w = 128 * 2;
		dst.x = STARTX - (dst.w / 2);
		dst.y = STARTY - (dst.h / 2);

		t_Fireball = SDLX_LoadTexture("Assets/Spells/Fireball.png", SDLX_DisplayGet());
		a_Fireball = calloc(4, sizeof(SDLX_Anim *));
		a_Fireball[0] = SDLX_AnimLoadHorizontal(t_Fireball,  6, 128, 98, SDLX_TRUE , 0, 98);
		a_Fireball[1] = SDLX_AnimLoadHorizontal(t_Fireball,  9, 128, 98, SDLX_TRUE, 0, 0);
		a_Fireball[2] = SDLX_AnimLoadHorizontal(t_Fireball,  8, 128, 98, SDLX_TRUE, 0, 197);
		a_Fireball[3] = SDLX_AnimLoadHorizontal(t_Fireball, 11,  64, 64, SDLX_TRUE, 0, 296);

		SDLX_SpriteCreate(&(ctx->spells[0].cast), t_Fireball, NULL, &dst);
		SDLX_SpriteCreate(&(ctx->spells[0].projectile), t_Fireball, NULL, &dst);
		SDLX_AnimatorCreate(&(ctx->spells[0].c_anim), a_Fireball, 3, &(ctx->spells[0].cast));
		SDLX_AnimatorCreate(&(ctx->spells[0].p_anim), &a_Fireball[3], 1, &(ctx->spells[0].projectile));
		ctx->spells[0].c_anim.active = SDLX_FALSE;
		ctx->spells[0].p_anim.active = SDLX_FALSE;
		ctx->spells[0].info.id = FBALL;
		ctx->spells[0].info.type = FIRE;
		ctx->spells[0].info.damage = 2;
		ctx->spells[0].info.duration = 10;
		ctx->spells[0].info.castTime = 7;
		ctx->spells[0].info.chargeTime = 8;
		ctx->spells[0].info.reaction = &fireball_react;
		ctx->spells[0].info.func = &Fireball;
		ctx->spells[0].cast.queue = 0;

		wasInit = 1;
	}
	return 0;
}

