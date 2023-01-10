#include "../../includes/main.h"


void drawSearchSquare(t_transform *transform, int pos)
{
    SDL_Rect rect;

    rect.h = SEARCHRANGE;
    rect.w = SEARCHRANGE;

	houghSpace_toScreen(pos, &rect.x, &rect.y, transform->canvW / 2, transform->canvH / 2);
    rect.x -=(SEARCHRANGE / 2);
    rect.y = rect.y + (transform->canvH / 2) - (SEARCHRANGE / 2);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 255, 255);
    SDL_RenderFillRect(SDLX_Display_Get()->renderer, &rect);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,255, 255, 255, 255);
}

void drawSearchLines(t_transform *transform)
{

	int lineX;
    int lineY;
	houghSpace_toScreen(
		(transform->visualizer.currentYDivide * HOUGHSPACE_W) + transform->visualizer.currentXDivide,
		&lineX, &lineY, transform->canvW / 2, transform->canvH / 2
		);

	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->searchTex);

	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 0);
	SDL_RenderClear(SDLX_Display_Get()->renderer);
	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);

	SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, transform->visualizer.currentYDivide, transform->canvW, transform->visualizer.currentYDivide);
	SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->visualizer.currentXDivide, 0, transform->visualizer.currentXDivide, transform->canvH);

	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
}

int unrolled_MaxInRange(t_transform *transform, int pos)
{
    int row;
    int col;
    int maxPos;
    int tryPos;

    maxPos = pos;
    col = -SEARCHRANGE;

	drawSearchSquare(transform, pos);
    while (col <= SEARCHRANGE)
    {
        row = -SEARCHRANGE;
        while (row <= SEARCHRANGE)
        {
            tryPos = pos + ((row * HOUGHSPACE_W) + col);
            if (tryPos >= 0 && tryPos < (HOUGHSPACE_W * HOUGHSPACE_H))
            {
                if (transform->houghSpace[tryPos] >= transform->houghSpace[maxPos])
                    maxPos = tryPos;
            }
            row++;
        }
        col++;
    }
    return maxPos;
}

int unrolled_HoughSpace_LocalMax(t_transform *transform, int start)
{

    if (start >= HOUGHSPACE_W * HOUGHSPACE_H || start < 0)
        return 1;

    if (!transform->visualizer.nextIndex)
        transform->visualizer.nextIndex = start;

    start = transform->visualizer.nextIndex;
    transform->visualizer.nextIndex = unrolled_MaxInRange(transform, start);
    if (transform->visualizer.nextIndex == start)
    {
        if (transform->maxIndex < 100 && transform->houghSpace[transform->visualizer.nextIndex] >= transform->treshold &&
		transform->visualizer.nextIndex != transform->maximums[transform->maxIndex])
        {
            transform->maximums[transform->maxIndex] = transform->visualizer.nextIndex;
            transform->maxIndex++;
        }
        transform->visualizer.nextIndex = 0;

        return 1;
    }
    return 0;
}

int unrolled_Divide(t_transform *transform)
{
    double stepX;
    double stepY;


    stepX = HOUGHSPACE_W / DIVIDE_X;
    stepY = HOUGHSPACE_H / DIVIDE_Y;

    SDL_Delay(50);
    if (transform->visualizer.currentXDivide < HOUGHSPACE_W)
    {

		drawSearchLines(transform);

        if (transform->visualizer.currentYDivide < HOUGHSPACE_H)
        {
            if (unrolled_HoughSpace_LocalMax (
                transform,
                (transform->visualizer.currentYDivide * HOUGHSPACE_W) + transform->visualizer.currentXDivide
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

	// if (transform->visualizer.shouldUpdate == 1)
    // {
    //     if (unrolled_Divide(transform))
    //         transform->visualizer.shouldUpdate++;
    //     SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->searchTex, NULL, &rect);
    // }

	rect.x += transform->canvW / 2;
    renderLinesUnbound(transform);

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);

	SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, transform->canvH / 2, transform->canvW, transform->canvH / 2);
    SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->canvW / 2, 0, transform->canvW / 2, transform->canvW);

	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->lines, NULL, &rect);
}
