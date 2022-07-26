#include "../../includes/main.h"

void houghSpace_toScreen(int position, int *x, int *y, int w, int h)
{
    *x = (position % HOUGHSPACE_W) * ((double)w / HOUGHSPACE_W);
    *y = (position / HOUGHSPACE_W) * ((double)h / HOUGHSPACE_H);
}

int scaleNumber_toRange(int input, SDL_Point fromRange, SDL_Point toRange)
{
    int		result;
	int		range;
	double	tmp;

	range = (fromRange.x - fromRange.y);

	tmp = input - fromRange.y;
	tmp /= range;
	tmp *= (toRange.x - toRange.y);
	result = tmp + toRange.y;

	return result;
}

void resetVisualizer(t_transform *transform)
{
		transform->visualizer.shouldUpdate = 0;
		transform->visualizer.currentXDivide = 0;
		transform->visualizer.currentYDivide = 0;
		transform->visualizer.nextIndex = 0;
}

void resetTransform(t_transform *transform)
{
	resetVisualizer(transform);
	transform->maxIndex = 0;
	transform->prevX = -1;
	transform->prevY = -1;
	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->drawSpace);
	SDL_RenderClear(SDLX_Display_Get()->renderer);
	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
	memset(transform->houghSpace, 0, sizeof(int) * HOUGHSPACE_W * HOUGHSPACE_H);
}

Uint8 getPixelColour(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;

    Uint8 *pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	// SDL_Log("This is pixel %p and foudn %p", surface->pixels, pixel);
	return *pixel;
}
