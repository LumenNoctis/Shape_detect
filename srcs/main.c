#include "../../includes/main.h"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

static SDLX_Display  	*display;
static t_transform		transform;

void mainLoop(void)
{
	SDLX_Render_Reset(display);
	SDLX_Input_Update();
	SDLX_InputLoop();
	handleInput(&transform);
	if (transform.mode == MODE_VISUALIZE)
		visualizer(&transform);
	else
		compute(&transform);

	// renderUI(transform);
	SDL_RenderPresent(display->renderer);
}

int main(void)
{
	SDLX_Start("SDLX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);

	display = SDLX_Display_Get();
	init(&transform);


	#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop(mainLoop, 0, 1);
	#endif
	#ifndef __EMSCRIPTEN__
		while(1)
			mainLoop();
	#endif
}
