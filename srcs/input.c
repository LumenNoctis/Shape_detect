#include "../../includes/main.h"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

void cleanup(t_transform *transform)
{
	SDL_DestroyTexture(transform->drawSpace);
	SDL_DestroyTexture(transform->searchTex);
	SDL_DestroyTexture(transform->lines);
	SDL_free(transform);
	exit(0);
}

void handleInput(t_transform *transform)
{
	SDLX_Display *display;
	SDLX_Input input;
	SDL_Event event;

	input = SDLX_Input_Get();
    while (SDL_PollEvent(&event))
    {
		#ifndef __EMSCRIPTEN__
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				cleanup(transform);

		#endif

		if  (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				transform->canvW = event.window.data1;
				transform->canvH = event.window.data2;
				SDL_SetWindowSize(display->window, event.window.data1, event.window.data2);
			}
        }
    }

	if (SDLX_GetKeyMapState(SDLX_TOGGLE) == SDLX_KEYUP)
    {
		transform->mode ^= 1;
		transform->prevX = -1;
		transform->prevY = -1;
		resetVisualizer(transform);
    }
	if (SDLX_GetKeyMapState(SDLX_RESTART) == SDLX_KEYUP)
	{
		transform->canDraw = 1;
		resetTransform(transform);
	}
	if (SDLX_GetKeyMapState(SDLX_PAUSE) == SDLX_KEYUP)
	{
		transform->canDraw ^= 1;
        divideNconquer(transform);
	}
	if (transform->mode == MODE_VISUALIZE && SDLX_GetKeyMapState(SDLX_LEFT) == SDLX_KEYUP)
	{
		transform->visualizer.shouldUpdate = 1;
		transform->treshold++;
		transform->maxIndex = 0;
		SDL_Log("New threshold %d", transform->treshold);
		resetVisualizer(transform);
	}
	if (transform->mode == MODE_VISUALIZE && SDLX_GetKeyMapState(SDLX_RIGHT) == SDLX_KEYUP)
	{
		transform->visualizer.shouldUpdate = 1;
		transform->treshold--;
		SDL_Log("New threshold %d", transform->treshold);
		transform->maxIndex = 0;
		resetVisualizer(transform);
	}
	if (!input.mouse_state && !transform->visualizer.shouldUpdate)
	{
		transform->visualizer.shouldUpdate = 1;
	}
	else if(input.mouse_state)
	{
		resetVisualizer(transform);
	}
}
