#include "../../includes/main.h"

void renderMaximums(t_transform *transform, int x_off, int y_off)
{
    SDL_Rect point;

    for (int i = 0; i < transform->maxIndex; i++)
    {
        point.h = 6;
        point.w = 6;
        // SDL_Log("here  %d", i);
        houghSpace_toScreen(transform->maximums[i], &point.x, &point.y, transform->canvW / 2, transform->canvW / 2);
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
        r = scaleNumber_toRange(transform->houghSpace[i] * transform->houghSpace[i], fromRange, toRange);
        b = 255 - r;
        if (transform->houghSpace[i] * transform->houghSpace[i] >= transform->treshold)
            SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,r, g, b, 255);
        if (transform->houghSpace[i])
        {
            houghSpace_toScreen(i, &x, &y, transform->canvW / 2, transform->canvH / 2);
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
            houghSpace_toScreen(i, &x, &y, transform->canvW / 2, transform->canvH / 2);
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
        y2 = -(transform->canvW * cos(theta) - d) / sin(theta);
        SDL_RenderDrawLine(
            display->renderer,
            0, y1,
            transform->canvW, y2
        );

    }
    SDL_SetRenderTarget(display->renderer, NULL);
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer,0, 0, 0, 255);
}

void renderGridAt(int x, int y, int w, int h, int gap)
{
    int i;
    int j;

    i = x;
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 50, 50, 50, 125);
    while (i < x + w)
    {
        SDL_RenderDrawLine(SDLX_Display_Get()->renderer,
            i, y, i, y + h
        );
        i += gap;
    }
    j = y;
    while (j < y + h)
    {
       SDL_RenderDrawLine(SDLX_Display_Get()->renderer,
            x, j, x + w, j
        );
        j += gap;
    }
    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

void renderUI(t_transform *transform)
{
    SDLX_Input input;
	SDL_Rect textbox;


    input = SDLX_Input_Get();

	if (transform->mode == MODE_COMPUTE)
	{
		char *text;

		if (transform->canDraw)
			text = "Click to draw. Press space to compute edges";
		else
			text = "Space to draw";
		SDLX_RenderMessage_Aligned(
			SDLX_Display_Get(),
			SDLX_CENTER_ALIGN,
			SDLX_BOTTOM_ALIGN,
			(SDL_Color){255, 255, 255},
			text
		);
		SDLX_RenderMessage_Aligned(
			SDLX_Display_Get(),
			SDLX_CENTER_ALIGN,
			SDLX_TOP_ALIGN,
			(SDL_Color){255, 255, 255},
			"Draw mode (tab to switch)"
		);
	}
	else
	{

		char *texts[4] = {"draw space","hough space", "heatmap (left/right to adjust)", "computed edges"};

		TTF_SizeText(SDLX_Display_Get()->defaultFont, texts[0], &textbox.w, &textbox.h);
		textbox.x = (transform->canvW / 4) - (textbox.w / 2);
		textbox.y = transform->canvH / 2  - textbox.h;
		SDLX_RenderMessage(SDLX_Display_Get(),
		&textbox, (SDL_Color){255, 255, 255}, texts[0]);

		TTF_SizeText(SDLX_Display_Get()->defaultFont, texts[1], &textbox.w, &textbox.h);
		textbox.x = (3 * (transform->canvW / 4)) - (textbox.w / 2);
		textbox.y = transform->canvH / 2  - textbox.h;
		SDLX_RenderMessage(SDLX_Display_Get(),
		&textbox, (SDL_Color){255, 255, 255}, texts[1]);


		TTF_SizeText(SDLX_Display_Get()->defaultFont, texts[2], &textbox.w, &textbox.h);
		textbox.x = (transform->canvW / 4) - (textbox.w / 2);
		textbox.y = transform->canvH  - textbox.h;
		SDLX_RenderMessage(SDLX_Display_Get(),
		&textbox, (SDL_Color){255, 255, 255}, texts[2]);


		TTF_SizeText(SDLX_Display_Get()->defaultFont, texts[3], &textbox.w, &textbox.h);
		textbox.x = (3 * (transform->canvW / 4)) - (textbox.w / 2);
		textbox.y = transform->canvH - textbox.h;
		SDLX_RenderMessage(SDLX_Display_Get(),
		&textbox, (SDL_Color){255, 255, 255}, texts[3]);

		SDLX_RenderMessage_Aligned(
			SDLX_Display_Get(),
			SDLX_CENTER_ALIGN,
			SDLX_TOP_ALIGN,
			(SDL_Color){255, 255, 255},
			"Visualize mode (tab to switch)"
		);
	}
    // In visualize mode :
        // - Mouse position in renderer lines (from mouse position in draw space)
        // - Subscript for each quarter (Image space | Parameter Space | Parameter Space Heatmap | Detected lines)
        // -

}
