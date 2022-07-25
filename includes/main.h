#ifndef MAIN_H
# define MAIN_H
# include "SDLX/SDLX.h"
# include "math.h"

# define WINDOW_NAME "Edge detection"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_W 500
# define WINDOW_H 500

# define DRAWSPACE_W WINDOW_W
# define DRAWSPACE_H WINDOW_H

# define HOUGHSPACE_W 360
# define HOUGHSPACE_H WINDOW_H

# define DIVIDE_X 6
# define DIVIDE_Y 6
# define SEARCHRANGE 50

#define MODE_COMPUTE 0
#define MODE_VISUALIZE 1

#define HALFSCREEN_W WINDOW_W / 2
#define HALFSCREEN_H WINDOW_H / 2

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define MAXTHRESHOLD 4

typedef struct  s_visualizer
{
    int currentXDivide;
    int currentYDivide;
    int shouldUpdate;
    int nextIndex;
}               t_visualizer;
typedef struct s_transform
{
    SDL_Texture *drawSpace;
    SDL_Texture *searchTex;
    SDL_Texture *lines;
    t_visualizer visualizer;

    int treshold;
    int mode;
    int houghSpace[HOUGHSPACE_W * HOUGHSPACE_H];
    int maximums[100];
    int maxIndex;

    int canvW;
    int canvH;
    int canDraw;
    int prevX;
    int prevY;
}               t_transform;

int     draw(t_transform *transform);
void    handleInput(t_transform *transform);

void    computeHough( int x, int y, int *arr, int w, int h);
void    divideNconquer(t_transform *transform);

void    visualizer(t_transform *transform);
void    compute(t_transform *transform);

void    renderMaximums(t_transform *transform, int x_off, int y_off);
void    renderDrawSpace(t_transform *transform);
void    renderDrawSpace_toDest(t_transform *transform, SDL_Rect dest);
void    renderHoughSpace_AsHeathMap(t_transform *transform, int off_x, int off_y);
void    renderHoughSpace_AsPoints(t_transform *transform,  int off_x, int off_y);
void    renderLinesUnbound(t_transform *transform);
void    renderGridAt(int x, int y, int w, int h, int gap);
void 	renderUI(t_transform *transform);

int     scaleNumber_toRange(int input, SDL_Point fromRange, SDL_Point toRange);
void    houghSpace_toScreen(int position, int *x, int *y, int w, int h);

void    resetVisualizer(t_transform *transform);
void    resetTransform(t_transform *transform);
#endif
