#include "main.h"

int renderMaximums(t_transform *transform)
{
    SDL_Rect point;

    for (int i = 0; i < transform->maxIndex; i++)
    {
        point.h = 6;
        point.w = 6;
        // SDL_Log("here  %d", i);
        houghSpace_toScreen(transform->maximums[i], &point.x, &point.y);
        point.x -= 3;
        point.y -= 3;
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 255, 100, 255);
        SDL_RenderDrawRect(
            SDLX_Display_Get()->renderer, &point);
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}

int renderDrawSpace(t_transform *transform)
{
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->drawSpace, NULL, NULL);
}

int renderHoughSpace_AsHeathMap(t_transform *transform)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    SDL_Point fromRange = {.x = 0, .y = transform->treshold};
    SDL_Point toRange = {.x = 0, .y = 255};
    int i;


    i = 0;
    g = 0;
    while (i < HOUGHSPACE_W * HOUGHSPACE_H)
    {
        r = scaleNumber_toRange(transform->houghSpace[i], fromRange, toRange);
        b = 255 - r;
        if (transform->houghSpace[i] >= transform->treshold)
            SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,r, g, b, 255);
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

int renderHoughSpace_AsPoints(t_transform *transform)
{
    int i;
    int x;
    int y;

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 125);
    i = 0;
    while (i < HOUGHSPACE_W * HOUGHSPACE_H)
    {
        if (transform->houghSpace[i])
        {
            houghSpace_toScreen(i, &x, &y);
            SDL_RenderDrawPoint (
                SDLX_Display_Get()->renderer, x, y);
        }
        i++;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

int renderLinesUnbound(t_transform *transform)
{
    static int print;
    SDLX_Display *display;
    double d;
    double theta;
    double y1, y2;
    double x1, x2;

    display = SDLX_Display_Get();
    for (int i = 0; i < transform->maxIndex; i++)
    {
        d = (transform->maximums[i] / HOUGHSPACE_W);
        theta = (transform->maximums[i] % HOUGHSPACE_W);
        theta = (theta * M_PI) / 180; 

        SDL_SetRenderDrawColor(display->renderer,0, 0, 255, 255);
        x1 = (d - 0 * sin(theta)) / cos(theta);
        x2 = (d - WINDOW_H * sin(theta))/ cos(theta);
        SDL_RenderDrawLine(
            display->renderer, 
            x1, 0,
            x2, WINDOW_H
        );
    }
    print++;
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}
