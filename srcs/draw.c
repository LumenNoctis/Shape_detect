#include "main.h"

int renderDrawSpace(t_transform *transform)
{
    int i;

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);
    i = 0;
    while (i < DRAWSPACE_W * DRAWSPACE_H)
    {
        // This will need to be rendered as lines instead of points
        if (transform->drawSpace[i])
            SDL_RenderDrawPoint (
                SDLX_Display_Get()->renderer,
                i % DRAWSPACE_W, i / DRAWSPACE_H
            );
        i++;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

int renderHoughSpace(t_transform *transform)
{
    int i;

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 125);
    i = 0;
    while (i < HOUGHSPACE_W * HOUGHSPACE_H)
    {
        if (transform->houghSpace[i])
        {
            SDL_RenderDrawPoint (
                SDLX_Display_Get()->renderer,
                (i % HOUGHSPACE_W) * ((double)WINDOW_W / HOUGHSPACE_W),
                (i / HOUGHSPACE_W) * ((double)WINDOW_H / HOUGHSPACE_H)
            );
        }
        i++;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

int renderLinesUnbound();


int draw(t_transform *transform)
{
    SDLX_Input input;
    SDLX_Display *display;

    display = SDLX_Display_Get();
    input = SDLX_Input_Get();
    SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

    if (input.mouse_state)
    {
        transform->drawSpace[DRAWSPACE_W * input.mouse.y + input.mouse.x] = 1;
        // SDL_Log("Compute at %d,%d from %d,%d scale(%d, %d) | (%f,%f)",
        //         input.mouse.x * (WINDOW_W / HOUGHSPACE_W),
        //         input.mouse.y * (WINDOW_H / HOUGHSPACE_H),
        //         input.mouse.x,
        //         input.mouse.y,
        //         (HOUGHSPACE_W / WINDOW_W),
        //         (HOUGHSPACE_H / WINDOW_H),
        //         (HOUGHSPACE_W / (double)WINDOW_W),
        //         (double)(HOUGHSPACE_H / (double)WINDOW_H)
        //         );
    
        computeHough(input.mouse.x * (HOUGHSPACE_W / (double)WINDOW_W),
                     input.mouse.y * (HOUGHSPACE_H / (double)WINDOW_H),
                     transform->houghSpace, HOUGHSPACE_W, HOUGHSPACE_H);
    }

    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

