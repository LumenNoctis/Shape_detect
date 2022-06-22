# include "main.h"

// typedef int(*visualizer_stage)(t_transform *);

int unrolled_MaxInRange(int range, int *arr, int w, int arraySize, int pos)
{
    SDL_Rect rect;
    int row;
    int col;
    int maxPos;
    int tryPos;
    
    maxPos = pos;
    col = -range;
    rect.h = range;
    rect.w = range;
    rect.x = (pos % HOUGHSPACE_W) * ((double)WINDOW_W / (double)HOUGHSPACE_W) - (range / 2);
    rect.y = (pos / HOUGHSPACE_W) * ((double)WINDOW_H / (double)HOUGHSPACE_H) - (range / 2);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 255, 255);
    while (col <= range)
    {
        row = -range;
        while (row <= range)
        {
            tryPos = pos + ((row * w) + col);
            if (tryPos >= 0 && tryPos < arraySize)
            {
                if (arr[tryPos] > arr[maxPos])
                    maxPos = tryPos;
            }
            row++;
        }
        col++;
    }
    SDL_RenderFillRect(SDLX_Display_Get()->renderer, &rect);
     SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,255, 255, 255, 255);
    return maxPos;
}

int unrolled_LocalMax(t_transform *transform, int arrLen, int start, int w)
{
    static int nextIndex;

    if (start >= arrLen || start < 0)
        return 1;

    if (!nextIndex)
        nextIndex = start;
        //  SDL_Log("COORD is it %f %f %d",
        //         (start % HOUGHSPACE_W) * ((double)WINDOW_W / (double)HOUGHSPACE_W), 
        //         (start / HOUGHSPACE_W) * ((double)WINDOW_H / (double)HOUGHSPACE_H),
        //         start
                // );
    start = nextIndex;
    nextIndex = unrolled_MaxInRange(SEARCHRANGE, transform->houghSpace, w, arrLen, start);
    if (nextIndex == start)
    {
        if (transform->maxIndex < 100 && nextIndex > MAXTHRESHOLD)
        {
            transform->maximums[transform->maxIndex] = nextIndex;
            transform->maxIndex++;
        }
        nextIndex = 0;
        return 1;
    }
    return 0;
}

int unrolled_Divide(t_transform *transform)
{
    static int X;
    static int Y;
    int stepX;
    int stepY;

    stepX = HOUGHSPACE_W / DIVIDE_X;
    stepY = HOUGHSPACE_H / DIVIDE_Y;

    SDL_Delay(100);
    if (Y <= DIVIDE_Y)
    {
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer,
            0, Y *stepY,
            WINDOW_W, Y *stepY
            );
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer,
            X * stepX, 0,
            X * stepX, WINDOW_H
            );
         SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
        if (X <= DIVIDE_X)
        {
            SDL_Log("STart here (%d,%d) at %d",(stepX * X), (stepY * Y * HOUGHSPACE_W), (stepY * Y * HOUGHSPACE_W) + (stepX * X));
            
            if (unrolled_LocalMax (
                transform, 
                HOUGHSPACE_W * HOUGHSPACE_H, 
                (stepY * Y * HOUGHSPACE_W) + (stepX * X), 
                HOUGHSPACE_W
            ))
            {
                X++;
            }
        }
        else
        {
            X = 0;
            Y++;
        }
       
    }
    else {
        X = 0;
        Y = 0;
        return 1;
    }
    return 0;
}

int drawAndShow(t_transform *transform)
{
    draw(transform);
    renderDrawSpace(transform);
    return 0;
}

int visualizer(t_transform *transform)
{
    // SDL_Log("Stage %d", transform->stage);
    if (!transform->stage)
    {
        drawAndShow(transform);
    }
    else
    {
        renderHoughSpace(transform);
        if (transform->stage == 1 && unrolled_Divide(transform))
        {
            transform->stage++;
            SDL_Log("Done dividing");
        }
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,255, 0, 0, 255);
        for (int i = 0; i < transform->maxIndex; i++)
        {
            SDL_Rect point;

            point.h = 4;
            point.w = 4;
            point.x = (transform->maximums[i] % HOUGHSPACE_W) * ((double)WINDOW_W / (double)HOUGHSPACE_W) - 2;
            point.y = (transform->maximums[i] / HOUGHSPACE_W) * ((double)WINDOW_H / (double)HOUGHSPACE_H) - 2;
            SDL_RenderDrawRect(
                SDLX_Display_Get()->renderer, &point);
        }
         SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
    }
}