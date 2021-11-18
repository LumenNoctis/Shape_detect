#include "rush.h"
// #include "debug.h"

SDLX_Animator *a;

int main(void)
{
	Context *ctx;
	SDL_Event e;
	SDLX_Display  *display;

	SDL_Log("Starting up\n");
	ctx = init_game();
	display = SDLX_DisplayGet();
	SDLX_LevelRun();
	// SDL_Log("ORI start%p", a->spriteptr->dstptr);
	// SDL_Log("ORI D %p R %p", display, display->renderer);

    while (1)
    {
		SDLX_ResetWindow();
		SDLX_InputUpdate(e);
        SDLX_InputLoop();
		SDLX_GUIUpdate();
		SDLX_AnimationUpdate();
		SDLX_LevelRun();

		# ifdef DEBUG
			debug(ctx);
		#endif
		// SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
		SDLX_Render_DisplayAll(display);
		SDL_RenderPresent(display->renderer);
		SDLX_FPSAdjust();
    }
}
