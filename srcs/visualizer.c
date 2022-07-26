#include "../../includes/main.h"

int unrolled_MaxInRange(int range, int *arr, int w, int arraySize, int pos, t_transform *transform)
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

    houghSpace_toScreen(pos, &rect.x, &rect.y, transform->canvW, transform->canvH);
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
	// SDL_Log("Macpos here at %d is %d", maxPos, arr[maxPos]);
    return maxPos;
}

int unrolled_LocalMax(t_transform *transform, int arrLen, int start, int w)
{

    if (start >= arrLen || start < 0)
        return 1;

    if (!transform->visualizer.nextIndex)
        transform->visualizer.nextIndex = start;

    start = transform->visualizer.nextIndex;
    transform->visualizer.nextIndex = unrolled_MaxInRange(SEARCHRANGE, transform->houghSpace, w, arrLen, start, transform);
    if (transform->visualizer.nextIndex == start)
    {
        if (transform->maxIndex < 100 && transform->houghSpace[transform->visualizer.nextIndex] >= transform->treshold &&
		transform->visualizer.nextIndex != transform->maximums[transform->maxIndex])
        {
			SDL_Log("Addded! %d at position %d", transform->houghSpace[transform->visualizer.nextIndex], transform->maxIndex);
            transform->maximums[transform->maxIndex] = transform->visualizer.nextIndex;
            transform->maxIndex++;
        }
        transform->visualizer.nextIndex = 0;
        return 1;
    }
    return 0;
    // unrolled_MaxInRange(SEARCHRANGE, transform->houghSpace, w, arrLen, start);
    // return 1;
}

int unrolled_Divide(t_transform *transform)
{
    double stepX;
    double stepY;

    int lineX;
    int lineY;

    stepX = HOUGHSPACE_W / DIVIDE_X;
    stepY = HOUGHSPACE_H / DIVIDE_Y;

    SDL_Delay(50);
    if (transform->visualizer.currentXDivide < HOUGHSPACE_W)
    {
        houghSpace_toScreen((transform->visualizer.currentYDivide * HOUGHSPACE_W) + transform->visualizer.currentXDivide, &lineX, &lineY, transform->canvW / 2, transform->canvH / 2);

        SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->searchTex);
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 0);
        SDL_RenderClear(SDLX_Display_Get()->renderer);
        SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, transform->visualizer.currentYDivide, transform->canvW, transform->visualizer.currentYDivide);
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->visualizer.currentXDivide, 0, transform->visualizer.currentXDivide, transform->canvH);

        if (transform->visualizer.currentYDivide < HOUGHSPACE_H)
        {
            if (unrolled_LocalMax (
                transform,
                HOUGHSPACE_W * HOUGHSPACE_H,
                (transform->visualizer.currentYDivide * HOUGHSPACE_W) + transform->visualizer.currentXDivide,
                HOUGHSPACE_W
            ))
            {
                transform->visualizer.currentYDivide += stepY;
            }
        }
        else
        {
            transform->visualizer.currentYDivide = 0;
            transform->visualizer.currentXDivide += stepX;
        }
       SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
    }
    else {
        transform->visualizer.currentXDivide = 0;
        transform->visualizer.currentYDivide = 0;
        return 1;
    }
    return 0;
}

int drawAndShow(t_transform *transform, int x, int y)
{
    SDL_Rect dst = {
        .x = x,
        .y = y,
        .w = transform->canvW / 2,
        .h = transform->canvH / 2
        };

    draw(transform);
    renderDrawSpace_toDest(transform, dst);
    return 0;
}

void visualizer(t_transform *transform)
{
    SDL_Rect rect;

    rect.h = transform->canvH / 2;
    rect.w = transform->canvW / 2;
    rect.x = 0;
    rect.y = 0;
    drawAndShow(transform, rect.x, rect.y);
    rect.x += transform->canvW / 2;
    renderHoughSpace_AsPoints(transform, rect.x, rect.y);
    renderGridAt(rect.x, rect.y, rect.w, rect.h, 10);
    rect.x = 0;
    rect.y += transform->canvH / 2;
    renderGridAt(rect.x, rect.y, rect.w, rect.h, 10);
    renderHoughSpace_AsHeathMap(transform, rect.x, rect.y);
    renderMaximums(transform, rect.x, rect.y);
    if (transform->visualizer.shouldUpdate == 1)
    {
        if (unrolled_Divide(transform))
            transform->visualizer.shouldUpdate++;
        SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->searchTex, NULL, &rect);
    }
    rect.x += transform->canvW / 2;
    renderLinesUnbound(transform);

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, transform->canvH / 2, transform->canvW, transform->canvH / 2);
    SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->canvW / 2, 0, transform->canvW / 2, transform->canvW);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->lines, NULL, &rect);
}
