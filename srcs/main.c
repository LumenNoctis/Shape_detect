#include "main.h"
// #include "debug.h"

t_transform *init(void)
{
	t_transform *transform;

	SDLX_InputMap(SDL_SCANCODE_TAB, 1, SDLX_TOGGLE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE, 1, SDLX_PAUSE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_R, 1, SDLX_RESTART, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT, 1, SDLX_LEFT, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT, 1, SDLX_RIGHT, 1, -1);

	transform = calloc(1, sizeof(t_transform));
	transform->treshold = MAXTHRESHOLD;
	transform->prevX = -1;
	transform->prevY = -1;
	transform->drawSpace = SDL_CreateTexture(
			SDLX_Display_Get()->renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			DRAWSPACE_W, DRAWSPACE_H
		);
	return transform;
}

int handleInput(t_transform *transform)
{
	SDLX_Input input;

	input = SDLX_Input_Get();

	if (input.input[SDLX_RESTART])
	{
		transform->stage = 0;
		transform->maxIndex = 0;
		transform->prevX = -1;
		transform->prevY = -1;
		SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->drawSpace);
		SDL_RenderClear(SDLX_Display_Get()->renderer);
		SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
		memset(transform->houghSpace, 0, sizeof(int) * HOUGHSPACE_W * HOUGHSPACE_H);
	}
	else if (SDLX_GetKeyMapState(SDLX_PAUSE) == 2)
	{
		transform->stage++;
		SDL_Log("Threshold changed to %d", transform->treshold);
	}
	else if (SDLX_GetKeyMapState(SDLX_LEFT) == 1 && transform->stage == 1)
	{
		transform->treshold--;
		
	}
	else if (SDLX_GetKeyMapState(SDLX_RIGHT) == 1 && transform->stage == 1)
		transform->treshold++;
}

int mainLoop(t_transform *transform)
{
	handleInput(transform);
	visualizer(transform);
}

int main(void)
{
	SDLX_Display  	*display;
	t_transform		*transform;

	SDLX_Start("Shape detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	display = SDLX_Display_Get();

	transform =	init();
    while (1)
    {
		SDLX_Render_Reset(display);
		SDLX_Input_Update();
        SDLX_InputLoop();
		mainLoop(transform);
		SDLX_RenderAll(display);
		SDL_RenderPresent(display->renderer);
    }
}
