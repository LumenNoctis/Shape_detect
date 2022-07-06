#include "../../includes/main.h"

void renderMaximums(t_transform *transform, int x_off, int y_off)
{
    SDL_Rect point;

    for (int i = 0; i < transform->maxIndex; i++)
    {
        point.h = 6;
        point.w = 6;
        // SDL_Log("here  %d", i);
        houghSpace_toScreen(transform->maximums[i], &point.x, &point.y, HALFSCREEN_W, HALFSCREEN_W);
        point.x = point.x + x_off - point.w;
        point.y = point.y + y_off - point.h;
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 255, 100, 255);
        SDL_RenderDrawRect(
            SDLX_Display_Get()->renderer, &point);
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}

void renderDrawSpace(t_transform *transform)
{
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->drawSpace, NULL, NULL);
}

void renderDrawSpace_toDest(t_transform *transform, SDL_Rect dest)
{
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->drawSpace, NULL, &dest);
}

void renderHoughSpace_AsHeathMap(t_transform *transform, int off_x, int off_y)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    SDL_Point fromRange = {.x = 0, .y = transform->treshold};
    SDL_Point toRange = {.x = 0, .y = 255};
    int i;
    int x;
    int y;

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
            houghSpace_toScreen(i, &x, &y, HALFSCREEN_W, HALFSCREEN_H);
            SDL_RenderDrawPoint (
                SDLX_Display_Get()->renderer,
                x + off_x, y + off_y
            );
        }
        i++;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

void renderHoughSpace_AsPoints(t_transform *transform,  int off_x, int off_y)
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
            houghSpace_toScreen(i, &x, &y, HALFSCREEN_W, HALFSCREEN_H);
            SDL_RenderDrawPoint (
                SDLX_Display_Get()->renderer, x + off_x, y + off_y);
        }
        i++;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

void renderLinesUnbound(t_transform *transform)
{
    SDLX_Display *display;
    double d;
    double theta;
    double y1, y2;
    double x1, x2;

    display = SDLX_Display_Get();
    SDL_SetRenderTarget(display->renderer, transform->lines);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 0);
    SDL_RenderClear(display->renderer);
    SDL_SetRenderDrawColor(display->renderer,0, 0, 255, 255);
    for (int i = 0; i < transform->maxIndex; i++)
    {
        d = (transform->maximums[i] / HOUGHSPACE_W);
        theta = (transform->maximums[i] % HOUGHSPACE_W);
        // SDL_Log("Theta %f distance %f", theta, d);
        theta = (theta * M_PI) / 180;

        y1 = -(0 * cos(theta) - d) / sin(theta);
        y2 = -(WINDOW_W * cos(theta) - d) / sin(theta);
        SDL_RenderDrawLine(
            display->renderer, 
            0, y1, 
            WINDOW_W, y2
        );

    }
    SDL_SetRenderTarget(display->renderer, NULL);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}
