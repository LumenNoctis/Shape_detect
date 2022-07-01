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

    houghSpace_toScreen(pos, &rect.x, &rect.y);
    rect.x -= (range / 2);
    rect.y -= (range / 2);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 255, 255);
    SDL_RenderFillRect(SDLX_Display_Get()->renderer, &rect);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,255, 255, 255, 255);

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
    return maxPos;
}

int unrolled_LocalMax(t_transform *transform, int arrLen, int start, int w)
{
    static int nextIndex;

    if (start >= arrLen || start < 0)
        return 1;

    if (!nextIndex)
        nextIndex = start;

    start = nextIndex;
    nextIndex = unrolled_MaxInRange(SEARCHRANGE, transform->houghSpace, w, arrLen, start);
    if (nextIndex == start)
    {
        if (transform->maxIndex < 100 && transform->houghSpace[nextIndex] > transform->treshold)
        {
            transform->maximums[transform->maxIndex] = nextIndex;
            transform->maxIndex++;
        }
        nextIndex = 0;
        return 1;
    }
    return 0;
    // unrolled_MaxInRange(SEARCHRANGE, transform->houghSpace, w, arrLen, start);
    // return 1;
}

int unrolled_Divide(t_transform *transform)
{
    static int X;
    static int Y;
    double stepX;
    double stepY;

    int lineX;
    int lineY;

    stepX = HOUGHSPACE_W / DIVIDE_X;
    stepY = HOUGHSPACE_H / DIVIDE_Y;

    SDL_Delay(100);
    if (X < HOUGHSPACE_W)
    {
        houghSpace_toScreen((Y * HOUGHSPACE_W) + X, &lineX, &lineY);
        
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);
        
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, lineY, WINDOW_W, lineY);
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer, lineX, 0, lineX, WINDOW_H);

        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
        if (Y < HOUGHSPACE_H)
        {
            if (unrolled_LocalMax (
                transform, 
                HOUGHSPACE_W * HOUGHSPACE_H, 
                (Y * HOUGHSPACE_W) + X, 
                HOUGHSPACE_W
            ))
            {
                Y += stepY;
            }
        }
        else
        {
            Y = 0;
            X += stepX;
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
    if (transform->stage == 0)
    {
        drawAndShow(transform);
    }
    else if (transform->stage == 1)
    {
        renderHoughSpace_AsHeathMap(transform);
        // renderHoughSpace_AsPoints(transform);
    } 
    else if (transform->stage == 2)
    {
        if (transform->stage == 2 && unrolled_Divide(transform))
            transform->stage++;
        renderHoughSpace_AsHeathMap(transform);
        renderMaximums(transform);
    }
    else
    {
        renderDrawSpace(transform);
        renderLinesUnbound(transform);
    }
}