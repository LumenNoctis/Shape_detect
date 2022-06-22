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


void SDLX_InputMap(int sdl_code, int type, int sdlx_code, int value, int controller_no)
{
	SDLX_KeyMap *new_mapping;

	// This could be a static array of MAX_MAPPING size, however it is unlikely that things will get
	// new mappins in the middle of a game, and I feel like a few small allocations as the game starts
	// won't be much of a drawback. This allows to have an arbitrary number of mappings
	// Though one can argue that it is unlikely that something will get mapped more than a certain amount
	// However linked lists also allow for easier unmapping since nodes can dynamically be removed
	// wheras arrays have a fixed number of indices and it would be troublesome to null them
	// But unmaping keys should also be fairly rare. All in all the pros and cons still have to be weighted
	// so I am going with what I find easiest at the moment.
	new_mapping = calloc(1, sizeof(SDLX_KeyMap));
	new_mapping->next = keymap;
	new_mapping->type = type;
	new_mapping->value = value;
	new_mapping->key = sdl_code;
	new_mapping->dest = &_intern_input.input[sdlx_code];
	new_mapping->controller_no = controller_no;
	keymap = new_mapping;
}

int SDLX_GetKeyMapState(int key)
{
	int state;
	int pstate;

	state = _intern_input.input[key];
	pstate = input_buffer[key];

	if (state > 0 && pstate > 0)
		return SDLX_KEYHELD;
	else if (state == 0 && pstate > 0)
		return SDLX_KEYUP;
	else if (state > 0 && pstate == 0)
		return SDLX_KEYDOWN;
	else
		return SDLX_NONE;
}


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