#include "main.h"
// #include "debug.h"

int main(void)
{
	SDLX_Display  *display;

	SDLX_Start("Shape detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	display = SDLX_Display_Get();

	// test_levelInit(NULL);
    while (1)
    {
		SDLX_Render_Reset(display);
		SDLX_Input_Update();
        SDLX_InputLoop();
		// test_level(NULL);
		SDLX_TimedLoop(draw, display);
		SDLX_RenderAll(display);
		SDL_RenderPresent(display->renderer);
		SDLX_CapFPS();
    }
}
