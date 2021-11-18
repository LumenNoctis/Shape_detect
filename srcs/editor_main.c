#include "SDLX.h"
#include "SDLX_editor.h"


int main(void)
{
	SDL_Event e;
	SDLX_Display  *display;

	SDLX_Start("SDLX Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	SDLX_EditorInit();
	display = SDLX_DisplayGet();
	while (1)
	{
		SDLX_ResetWindow();
		SDLX_InputUpdate(e);
		SDLX_InputLoop();
		SDLX_EditorRun();

		SDLX_Render_DisplayAll(display);
		SDL_RenderPresent(display->renderer);
		SDLX_FPSAdjust();
	}
}
