#include "rush.h"

void NullGUIFunc(SDLX_GUIElem *elem){return ;};

void select_enter(SDLX_GUIElem *elem)
{
	SDL_Log("Enter\n");
	SDLX_Animator_StateSet(elem->animator, 1, SDLX_NONE);
}

void click(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(elem->animator, 2, SDLX_NONE);
			SDL_Log("Clicked\n");

}
void clickexit(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(elem->animator, 0, SDLX_NONE);
			SDL_Log("Clickced agane \n");
}

void SelectExit_button(SDLX_GUIElem *elem)
{
	SDL_Log("Exit\n");
	SDLX_Animator_StateSet(elem->animator, 0, SDLX_AWAITANIM);
}

Context *init(void)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;
	SDL_Texture *tex;
	SDL_Rect dst;

	Context *ctx;

	dst.x = WIN_W / 2 - 32;
	dst.y = WIN_W / 2 - 64;
	dst.w = 64;
	dst.h = 64;

    SDLX_Start("Rush", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	ctx = calloc(1, sizeof(*ctx));
	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/Button_SpriteSheet.png"));

	anim = calloc(3, sizeof(SDLX_Anim));
	anim[2] = SDLX_AnimLoad(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 0);
	anim[0] = SDLX_AnimLoad(tex, 1, 64, 64, SDL_TRUE, 0, 0);
	anim[1] = SDLX_AnimLoad(tex, 8, 64, 64, SDL_FALSE, 64, 0);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst);
	animator->state = 0;
	ctx->buttons[0] = SDLX_GUIElem_Create(animator, "Start", &select_enter, &SelectExit_button, &NullGUIFunc, NullGUIFunc, click, clickexit);
	SDLX_GUIElem_SetActive(ctx->buttons[0], SDLX_TRUE);

	// dst.x = WIN_W / 2 - 32;
	// dst.y = WIN_W / 2;
	// dst.w = 64;
	// dst.h = 64;
	// anim = calloc(3, sizeof(SDLX_Anim));
	// anim[2] = SDLX_AnimLoad(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 64);
	// anim[0] = SDLX_AnimLoad(tex, 1, 64, 64, SDL_TRUE, 0, 64);
	// anim[1] = SDLX_AnimLoad(tex, 8, 64, 64, SDL_FALSE, 64, 64);
	// animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst);
	// animator->state = 0;
	// ctx->buttons[1] = SDLX_GUIElem_Create(animator, "Exit", &select_enter, &SelectExit_button, &NullGUIFunc, NullGUIFunc, click, clickexit);
	// SDLX_GUIElem_SetActive(ctx->buttons[1], SDLX_TRUE);

	return ctx;
}


int main(void)
{
	Context *ctx;
	SDL_Event e;
	SDLX_Display  *display;

	ctx = init();
	SDL_Log("Init\n");
	display = SDLX_DisplayGet();
    while (1)
    {
		SDLX_ResetWindow();
        SDLX_InputLoop();
		SDLX_InputUpdate(e);
		SDLX_GUIUpdate();
		SDLX_AnimationUpdate();

		SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
		SDL_RenderPresent(SDLX_DisplayGet()->renderer);
		SDLX_FPSAdjust();
    }
}