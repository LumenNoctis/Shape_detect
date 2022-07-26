#include "../../includes/main.h"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

static SDLX_Display  	*display;
static t_transform		*transform;

t_transform *init(void)
{
	t_transform *transform;

	SDLX_InputMap(SDL_SCANCODE_TAB, 	1, SDLX_TOGGLE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE,	1, SDLX_PAUSE, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_R, 		1, SDLX_RESTART,1, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT,	1, SDLX_LEFT, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT,	1, SDLX_RIGHT,	1, -1);

	transform = calloc(1, sizeof(t_transform));
	transform->treshold = MAXTHRESHOLD;
	transform->prevX = -1;
	transform->prevY = -1;
	transform->canDraw = 1;
	transform->canvW = WINDOW_W;
	transform->canvH = WINDOW_H;
	transform->drawSpace = SDL_CreateTexture(
			SDLX_Display_Get()->renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			DRAWSPACE_W, DRAWSPACE_H
		);
	transform->lines = SDL_CreateTexture(
			SDLX_Display_Get()->renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			DRAWSPACE_W, DRAWSPACE_H
		);

	transform->searchTex = SDL_CreateTexture(
			SDLX_Display_Get()->renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			DRAWSPACE_W, DRAWSPACE_H
		);
	SDL_SetTextureBlendMode(transform->lines, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->drawSpace, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->searchTex, SDL_BLENDMODE_BLEND);
	return transform;
}

void mainLoop(void)
{
	SDLX_Render_Reset(display);
	SDLX_Input_Update();
	SDLX_InputLoop();
	handleInput(transform);
	if (transform->mode == MODE_VISUALIZE)
		visualizer(transform);
	else
		compute(transform);

	renderUI(transform);
	SDLX_RenderAll(display);
	SDL_RenderPresent(display->renderer);
}

int main(void)
{
	SDLX_Start("Shape detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
	display = SDLX_Display_Get();

	transform =	init();

	#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop(mainLoop, 0, 1);
	#endif
	#ifndef __EMSCRIPTEN__
		while(1)
			mainLoop();
	#endif

    // while (1)
    // {
	// 	SDLX_Render_Reset(display);
	// 	SDLX_Input_Update();
    //     SDLX_InputLoop();
	// 	mainLoop(transform);
	// 	SDLX_RenderAll(display);
	// 	SDL_RenderPresent(display->renderer);
    // }
}
