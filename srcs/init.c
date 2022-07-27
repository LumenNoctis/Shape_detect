#include "../../includes/main.h"

void init(t_transform *transform)
{

	SDLX_Display *display;
	SDL_Surface *surf;

	SDLX_InputMap(SDL_SCANCODE_TAB, 	1, SDLX_TOGGLE, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE,	1, SDLX_PAUSE, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_R, 		1, SDLX_RESTART,1, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT,	1, SDLX_LEFT, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT,	1, SDLX_RIGHT,	1, -1);

	display = SDLX_Display_Get();
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

	surf = TTF_RenderText_Solid(display->defaultFont, "Click to draw. Press space to compute edges", (SDL_Color){255, 255, 255});
	transform->drawText = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "Space to draw", (SDL_Color){255, 255, 255});
	transform->edgeText = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "Draw mode (tab to switch)", (SDL_Color){255, 255, 255});
	transform->drawModeText = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "Visualize mode (tab to switch)", (SDL_Color){255, 255, 255});
	transform->visualizeModeText = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "draw space", (SDL_Color){255, 255, 255});
	transform->quadrantText[0] = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "hough space", (SDL_Color){255, 255, 255});
	transform->quadrantText[1]  = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "heatmap (left/right to adjust)", (SDL_Color){255, 255, 255});
	transform->quadrantText[2]  = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(display->defaultFont, "computed edges", (SDL_Color){255, 255, 255});
	transform->quadrantText[3]  = SDL_CreateTextureFromSurface(
		display->renderer, surf);
	SDL_FreeSurface(surf);

	SDL_SetTextureBlendMode(transform->lines, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->drawSpace, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->searchTex, SDL_BLENDMODE_BLEND);

	SDL_SetTextureBlendMode(transform->drawText, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->edgeText, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->drawModeText, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->visualizeModeText , SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->quadrantText[0], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->quadrantText[1], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->quadrantText[2], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(transform->quadrantText[3], SDL_BLENDMODE_BLEND);
}
