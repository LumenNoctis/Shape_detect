#include "SDLX/SDLX.h"
#include <time.h>

typedef struct	SDLX_KeyMap
{
	int key;
	int type;
	int	*dest;
	int value;
	int controller_no;

	struct SDLX_KeyMap *next;
}	SDLX_KeyMap;

static SDLX_Input _intern_input;
static SDLX_KeyMap *keymap;
static int input_buffer[SDLX_INPUT_AMOUNT];


void 		SDLX_InputResetBuffer(void)
{
	SDL_memcpy4(input_buffer, _intern_input.input, SDLX_INPUT_AMOUNT);
	SDL_memset4(_intern_input.input, 0, SDLX_INPUT_AMOUNT);
	_intern_input.mouse_click = SDLX_FALSE;
	_intern_input.key_down = SDLX_NONE;
}
void _GetInputState(SDLX_KeyMap 	*map_node)
{
	const Uint8		*keyboard;
	int input_val;

	keyboard = SDL_GetKeyboardState(NULL);

	if (map_node->type == SDLX_KEYBOARD)
		input_val = (keyboard[map_node->key] * map_node->value);
	// else if (map_node->type == SDLX_CONTROLLER)
	// {
	// 	input_val = SDL_GameControllerGetButton(
	// 						SDL_GameControllerFromPlayerIndex(map_node->controller_no),// Getting undefined reference here, not sure why
	// 						map_node->key);
	// }
	*(map_node->dest) |= (input_val * map_node->value);
}

void SDLX_InputLoop(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit(0);
	}
}

void SDLX_Input_Update()
{
	// SDL_Event	events[3];
	Uint32		newMouseState;
	// int e;

	newMouseState = SDL_GetMouseState(&_intern_input.mouse.x, &_intern_input.mouse.y);
	SDL_GetRelativeMouseState(&_intern_input.mouse_delta.x, &_intern_input.mouse_delta.y);
	SDLX_KeyMap 	*map_node;
	SDL_Event		e[1];
	int				controller_button;
	int 			eNum;

	map_node = keymap;

	SDL_PumpEvents();

	SDLX_InputResetBuffer();
	map_node = keymap;
	while (map_node)
	{
		_GetInputState(map_node);
		map_node = map_node->next;
	}

	_intern_input.mouse_state = ((_intern_input.mouse_state & 1) << 1) + newMouseState;
}

SDLX_Input SDLX_Input_Get() { return _intern_input; }