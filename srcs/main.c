#include "main.h"
// #include "debug.h"

t_transform *init(void)
{
	t_transform *transform;

	transform = calloc(1, sizeof(t_transform));
	SDLX_InputMap(SDL_SCANCODE_TAB, 1, SDLX_TOGGLE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE, 1, SDLX_PAUSE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_R, 1, SDLX_RESTART, 1, -1);

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
		memset(transform->drawSpace, 0, sizeof(int) * DRAWSPACE_W * DRAWSPACE_H);
		memset(transform->houghSpace, 0, sizeof(int) * HOUGHSPACE_W * HOUGHSPACE_H);
	}
	else if (input.input[SDLX_TOGGLE])
	{
		transform->mode ^= 1;
		transform->stage = 0;
	}
	else if (input.input[SDLX_PAUSE])
		transform->stage = 1;

	SDLX_InputResetBuffer();
}

int mainLoop(t_transform *transform)
{
	handleInput(transform);
	// SDL_Log("TRansform  %d %d %d", transform->mode, transform->stage, transform->maxIndex);
	// if (!transform->mode)
		visualizer(transform);
	// else
	// 	compute(transform);
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
		// test_level(NULL);
		mainLoop(transform);
		// SDLX_TimedLoop(mainLoop, transform1);
		SDLX_RenderAll(display);
		SDL_RenderPresent(display->renderer);
		// SDLX_CapFPS();
    }
}
