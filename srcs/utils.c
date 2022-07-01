#include "main.h"

void houghSpace_toScreen(int position, int *x, int *y)
{
    *x = (position % HOUGHSPACE_W) * ((double)WINDOW_W / HOUGHSPACE_W);
    *y = (position / HOUGHSPACE_W) * ((double)WINDOW_H / HOUGHSPACE_H);
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