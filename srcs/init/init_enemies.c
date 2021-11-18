
// #include "rush_structs.h"
# include "enemies.h"
# include "core_structs.h"

Formation _formations_data[1];
Enemy 	 _enemy_data[50];

Context *getCtx(void);

void init_enemyData(void)
{
	static int WasInit;
	int offset;
	Context	*ctx;
	SDLX_Anim  **anim;
	SDL_Texture *tex;

	if (!WasInit)
	{
		ctx = getCtx();

		offset = 0;
		tex = SDLX_LoadTexture("Assets/Enemies/Skull.png", SDLX_DisplayGet());
		anim = calloc(3, sizeof(SDLX_Anim *));
		anim[0] = SDLX_AnimLoadHorizontal(tex, 8, 64, 69, SDLX_TRUE, 0, 0);
		anim[1] = SDLX_AnimLoadHorizontal(tex, 8, 64, 69, SDLX_FALSE, 0, 69);
		anim[2] = SDLX_AnimLoadHorizontal(tex, 8, 64, 69, SDLX_FALSE, 0, 69 * 2);

		SDLX_SpriteCreate(&E_SKULL.sprite, tex, NULL, NULL);
		SDLX_AnimatorCreate(&E_SKULL.animator, anim, 3, &E_SKULL.sprite);

		E_SKULL.info.id = 1;
		E_SKULL.info.hp = 20;
		E_SKULL.info.speed = 2;
		E_SKULL.info.type = FIRE;
		E_SKULL.info.func = &skullfn;
		E_SKULL.animator.active = SDLX_FALSE;

		F_ADD(F_SINGLE, E_SKULL, WIN_W / 2, WIN_H / 2, 128, 128, offset);
		F_ADD(F_SINGLE, E_SKULL, WIN_W / 3, WIN_H / 3, 64, 64, offset);
	}
}

void init_enemies(void)
{
	Context *ctx;
	SDL_Texture *tex;
	int i;

	i = 0;
	static int WasInit;

	if (!WasInit)
	{
		ctx = getCtx();
		while (i < 50)
		{
			SDLX_SpriteCreate(&ctx->enemy_data[i].sprite, NULL, NULL, NULL);
			SDLX_AnimatorCreate(&ctx->enemy_data[i].animator, NULL, 0, &ctx->enemy_data[i].sprite);
			SDLX_ColliderCreate(L_ENEMY, 0, ctx->enemy_data[i].sprite.dst
				,&ctx->enemy_data[i].collider, SDLX_DefaultCollision, e_react
				,&ctx->enemy_data[i].info);
				ctx->enemy_data[i].animator.active = SDLX_FALSE;
			i++;
		}
		WasInit = 1;
	}
}
