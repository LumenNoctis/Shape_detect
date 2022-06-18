#include "main.h"
#include "math.h"

static int drawbuffer[(WINDOW_H) * (WINDOW_W)];

int drawWave(SDLX_Display *display, int x, int y)
{
    int angle = 0;
    double theta;
    int d = 0;
    while (angle < WINDOW_W / 2)
    {
        theta = (angle * M_PI) / 180;
        d = x * cos(theta) + y * sin(theta);
        // SDL_Log("Here %d %d %d", theta, angle, d);
        if (d * WINDOW_W + angle + (WINDOW_W / 2) > 0 &&
            d * WINDOW_W + angle + (WINDOW_W / 2) < WINDOW_H * WINDOW_W)
            drawbuffer[d * WINDOW_W + angle + (WINDOW_W / 2)] += 1;
        angle++;
    }
}

int draw(SDLX_Display *display)
{
    SDLX_Input input;
    int i;


    input = SDLX_Input_Get();
    SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(display->renderer, WINDOW_W / 2, 0, WINDOW_W / 2, WINDOW_H);

    if (input.mouse.x < (WINDOW_W / 2) &&
        input.mouse_state)
    {
        drawbuffer[WINDOW_W * input.mouse.y + input.mouse.x] += 1;
        drawWave(display,input.mouse.x, input.mouse.y);
    }

    i = 0;
    while (i < WINDOW_H * WINDOW_W)
    {
        if (drawbuffer[i])
        {
            SDL_RenderDrawPoint(display->renderer, i % WINDOW_W, i / WINDOW_W);
        }
        i++;
    }

    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}