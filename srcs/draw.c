#include "main.h"

int renderDrawSpace(t_transform *transform)
{
    // int i;
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->drawSpace, NULL, NULL);
    // SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);
    // i = 0;
    // while (i < HOUGHSPACE_W * HOUGHSPACE_H)
    // {
    //     // This will need to be rendered as lines instead of points
    //     if (transform->houghSpace[i])
    //         SDL_RenderDrawPoint (
    //             SDLX_Display_Get()->renderer,
    //             i % HOUGHSPACE_W, i / HOUGHSPACE_H
    //         );
    //     i++;
    // }
    // SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
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

int renderLinesUnbound(t_transform *transform)
{
    // (x + d) / sin(0) = y;
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

        // SDL_Log("Angle %d is %f at %f", i, theta, d);
        SDL_SetRenderDrawColor(display->renderer,0, 255, 0, 255);

     
        // x1 = -((0 * cos(theta) - d)) / sin(theta);
        // x2 = -((WINDOW_W * cos(theta) - d))/ sin(theta);

        
        SDL_SetRenderDrawColor(display->renderer,0, 0, 255, 255);
        x1 = (d - 0 * sin(theta)) / cos(theta);
        x2 = (d - WINDOW_H * sin(theta))/ cos(theta);
         SDL_RenderDrawLine(display->renderer, 
            x1, 0,
            x2, WINDOW_H);
        
    

        // SDL_RenderDrawLine(display->renderer, 
        //     0, y1,
        //     WINDOW_W, y2);
    }
    print++;
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}


int draw(t_transform *transform)
{
    SDLX_Input input;
    SDLX_Display *display;
    double slope;
    double b;
    int stepAmount;
    int stepDir;
    int x;
    int y;

    display = SDLX_Display_Get();
    input = SDLX_Input_Get();
    SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

    if (input.mouse_state )
    {
        if (input.mouse_delta.x && input.mouse_delta.y)
        {

            if (transform->prevX == -1 && transform->prevY == -1)
            {
                transform->prevX = input.mouse.x;
                transform->prevY = input.mouse.y;
                return 0;
            }
            
            // SDL_Log("??? wut1");
            if (input.mouse.x - transform->prevX == 0)
            {
                slope = 0;
                stepAmount = abs(input.mouse.x - transform->prevX);
            }
            else
            {
                slope = (input.mouse.y - transform->prevY) / (input.mouse.x - transform->prevX);
                stepAmount = abs(input.mouse.y - transform->prevY);
            }
            b = -(input.mouse.x * slope) + input.mouse.y;
            stepDir = (input.mouse.x - transform->prevX > 0 ? 1 : -1);


            for (int i = 0; i < stepAmount; i++)
            {
                x = transform->prevX + (stepDir * i);
                y = x * slope + b;
                computeHough(x * (HOUGHSPACE_W / (double)WINDOW_W),
                            y * (HOUGHSPACE_H / (double)WINDOW_H),
                            transform->houghSpace, HOUGHSPACE_W, HOUGHSPACE_H);
            }
            SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->drawSpace);
            SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->prevX , transform->prevY, input.mouse.x, input.mouse.y);
            SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
            
            transform->prevX = input.mouse.x;
            transform->prevY = input.mouse.y;
        }
    }
    else
    {
        transform->prevX = -1;
        transform->prevY = -1;
    }

    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    return 0;
}

