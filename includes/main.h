#ifndef MAIN_H
# define MAIN_H
# include "SDLX/SDLX.h"

# define WINDOW_NAME "Edge detection"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500

void	test_levelInit(void *args);
int		test_level(void *args);
int     draw(SDLX_Display *display);

#endif
