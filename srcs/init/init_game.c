# include "rush.h"

static Context ctx;


Context *getCtx(void){return &ctx;}

Context *init_game(void)
{
	SDL_Texture *tex;

    SDLX_Start("The Mage", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	SDLX_InputMap(SDL_SCANCODE_UP,		SDLX_KEYBOARD, SDLX_UP, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_W,		SDLX_KEYBOARD, SDLX_UP,		0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_DOWN,	SDLX_KEYBOARD, SDLX_DOWN,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_S, 		SDLX_KEYBOARD, SDLX_DOWN,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT,	SDLX_KEYBOARD, SDLX_LEFT,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_A,		SDLX_KEYBOARD, SDLX_LEFT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT,	SDLX_KEYBOARD, SDLX_RIGHT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_D,		SDLX_KEYBOARD, SDLX_RIGHT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE, 	SDLX_KEYBOARD, SDLX_PAUSE, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_KP_ENTER,SDLX_KEYBOARD, SDLX_PAUSE, 	0b00000001, -1);

	SDLX_GUI_KeyMap(SDLX_UP, SDLX_DOWN, SDLX_LEFT, SDLX_RIGHT, SDLX_PAUSE);

	// tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/phBG.png"));
	// SDLX_BackgroundSet(tex);

	// SDLX_LevelManagerAdd(0, main_menuInit, main_menu, main_menuCleanup);
	SDLX_LevelManagerAdd(0, main_levelInit, main_level, main_levelCleanup);
	// SDLX_LevelManagerAdd(0, test_levelInit, test_level, test_levelCleanup);
	// SDLX_LevelManagerAdd(2, test_levelInit, test_level, test_levelCleanup);
	SDLX_LevelManagerStart(0, &ctx);
	SDL_Log("Init Game\n");
	return &ctx;
}
