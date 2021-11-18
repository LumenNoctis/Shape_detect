#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include "SDLX.h"

# define MAX_ACTIVE_SPELLS 10

typedef struct Enemy Enemy;
typedef int (*EnemyFn)(Enemy *);
typedef int (*SpellFn)();

enum
{
	L_ENEMY = 0b0001,
	L_SPELL = 0b0010,
	L_PLAYER = 0b0100,
};

enum
{
	FIRE = 0,
	ICE,
	EARTH,
	WATER,
	LIGHT,
	SHADOW
};

typedef struct Enemy_Info
{
	int			id;
	int 		hp;
	int			type;
	int			speed;
	EnemyFn		func;

	SDL_Rect 	hitbox;
}				Enemy_Info;

typedef struct Enemy
{
	Enemy_Info	info;

	SDLX_Sprite sprite;
	SDLX_Collider collider;
	SDLX_Animator animator;

}				Enemy;

typedef struct Formation
{
	Enemy		enemies[50];
	int 		nenemies;

}				Formation;

typedef struct  SpellInfo
{
	int 		id;
	int 		cd;
	int 		cost;
	int			type;
	int			damage;
	int			active;
	int 		duration;
	int 		castTime;
	int 		chargeTime;
	int 		*state;
	int 		*elapsed;

	const char *name;
	SDLX_ReactionFn reaction;
	SpellFn func;

}				SpellInfo;

typedef struct Spell
{
	SpellInfo info;

	SDL_Point	step;
	SDLX_Sprite cast;
	SDLX_Sprite projectile;
	SDLX_Animator p_anim;
	SDLX_Animator c_anim;

	SDLX_Collider collider;
}			Spell;

typedef struct PlayerData
{
	Spell		active[10];
	Spell		*current;

	SDLX_Collider collider;

	int hp;
	int mana;
	int exp;
	int maxHP;
	int maxMana;
}				PlayerData;

#endif
