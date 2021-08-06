#include "SDLX_LevelManager.h"
#include "SDLX_input.h"

typedef struct SDLX_LvlManager
{
	int currentLevel;
	SDLX_LevelFunc levels[MAX_LEVELS][3];

}			SDLX_LvlManager;

# define INIT 0
# define CLEANUP 1
# define LOOP 2

static SDLX_LvlManager manager;
static void *manargs;

void SDLX_LevelManagerAdd(int level, SDLX_LevelFunc lvlInit, SDLX_LevelFunc lvlLoop, SDLX_LevelFunc lvlCleanUp)
{
	manager.levels[level][INIT] = lvlInit;
	manager.levels[level][CLEANUP] = lvlCleanUp;
	manager.levels[level][LOOP] = lvlLoop;
}

void SDLX_LevelManagerStart(int level, void *args)
{
	SDL_Log("Starting with  lvl %d \n", level);
	manager.currentLevel = level;
	manargs = args;
	manager.levels[manager.currentLevel][INIT](manargs);
}

void SDLX_LevelManagerSwitch(int level, void *args)
{
	SDL_Log("Switch from %d to %d\n", manager.currentLevel, level);
	if (manager.levels[manager.currentLevel][CLEANUP])
		manager.levels[manager.currentLevel][CLEANUP](NULL);
	SDLX_InputResetBuffer();
	if (manager.levels[level][INIT])
		manager.levels[level][INIT](NULL);

	manager.currentLevel = level;
	manargs = args;
}

void SDLX_LevelRun(void)
{
	manager.levels[manager.currentLevel][LOOP](manargs);
}
