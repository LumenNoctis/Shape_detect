#include "../../includes/main.h"

void handleInput(t_transform *transform)
{
	SDLX_Input input;

	input = SDLX_Input_Get();

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
		// SDL_Log("AAAA %d",);
		transform->canDraw ^= 1;
        divideNconquer(transform);
	}
	if (transform->mode == MODE_VISUALIZE && SDLX_GetKeyMapState(SDLX_LEFT) == SDLX_KEYUP)
	{
		transform->visualizer.shouldUpdate = 1;
		transform->treshold++;
		transform->maxIndex = 0;
		resetVisualizer(transform);
	}
	if (transform->mode == MODE_VISUALIZE && SDLX_GetKeyMapState(SDLX_RIGHT) == SDLX_KEYUP)
	{
		transform->visualizer.shouldUpdate = 1;
		transform->treshold--;
		transform->maxIndex = 0;
		resetVisualizer(transform);
	}
	if (!input.mouse_state && !transform->visualizer.shouldUpdate)
	{
		transform->visualizer.shouldUpdate = 1;
	}
	else if(input.mouse_state)
	{
		transform->visualizer.shouldUpdate = 0;
	}
}