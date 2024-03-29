#include "../../includes/main.h"

void scaleMousePos(t_transform *transform, SDL_Point *mouse)
{
	SDL_Point fromRangex = {.x = 0, transform->canvW / 2};
	SDL_Point fromRangey = {.x = 0, transform->canvH / 2};
	SDL_Point toRangex = {.x = 0, transform->canvW};
	SDL_Point toRangey = {.x = 0, transform->canvH};

	mouse->x = scaleNumber_toRange(mouse->x, fromRangex, toRangex);
	mouse->y = scaleNumber_toRange(mouse->y, fromRangey, toRangey);
}

void drawUserInput(t_transform *transform, SDL_Point mouse)
{
	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);
	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->drawSpace);
	SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->prevX , transform->prevY, mouse.x, mouse.y);
	SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);
	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
}

void calcLine(t_transform *transform, SDL_Point mouse)
{
	double slope;
    double b;
    int stepAmount;
    int stepDir;
	int x;
	int y;


	if (mouse.x - transform->prevX == 0)
	{
		slope = 0;
		stepAmount = 1;
	}
	else
	{
		slope = (mouse.y - transform->prevY) / (mouse.x - transform->prevX);
		// stepAmount = mouse.x - transform->prevX ;
		stepAmount = 1;
	}
	b = -(mouse.x * slope) + mouse.y;
	stepDir = (mouse.x - transform->prevX > 0 ? 1 : -1);


	for (int i = 0; i < stepAmount; i++)
	{
		x = transform->prevX + stepDir;
		y = x * slope + b;
		computeHough(x, y, transform->houghSpace, HOUGHSPACE_W, HOUGHSPACE_H);
	}
}

int draw(t_transform *transform)
{
    SDLX_Input input;
    int x;
    int y;

    input = SDLX_Input_Get();


    if (input.mouse_state )
    {

        if (
			(input.mouse_delta.x || input.mouse_delta.y)
			&&
			(
				(
					(transform->mode == MODE_VISUALIZE) &&
					input.mouse.x < transform->canvW / 2 &&
					input.mouse.y < transform->canvH / 2
				)
            ||
				(
					transform->mode == MODE_COMPUTE
				)
			)
		)
        {
            if (transform->mode == MODE_VISUALIZE)
               scaleMousePos(transform, &input.mouse);

            if (transform->prevX == -1 && transform->prevY == -1)
            {
                transform->prevX = input.mouse.x;
                transform->prevY = input.mouse.y;

                return 0;
            }

			calcLine(transform, input.mouse);
			drawUserInput(transform, input.mouse);

            transform->prevX = input.mouse.x;
            transform->prevY = input.mouse.y;
        }
    }
    else
    {
        transform->prevX = -1;
        transform->prevY = -1;
    }


    return 0;
}

// int draw(t_transform *transform)
// {
//     SDLX_Input input;
//     SDLX_Display *display;
//     double slope;
//     double b;
//     int stepAmount;
//     int stepDir;
//     int x;
//     int y;

//     display = SDLX_Display_Get();
//     input = SDLX_Input_Get();
//     SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

//     if (input.mouse_state )
//     {
//         if ((
//             (transform->mode == MODE_VISUALIZE) &&
//              input.mouse.x < transform->canvW / 2 &&
//              input.mouse.y < transform->canvH / 2 &&
//              input.mouse_delta.x &&
//              input.mouse_delta.y
//             )
//             ||
//             (transform->mode == MODE_COMPUTE &&
//             input.mouse_delta.x &&
//             input.mouse_delta.y))
//         {
//             if (transform->mode == MODE_VISUALIZE)
//             {
//                 SDL_Point fromRangex = {.x = 0, transform->canvW / 2};
//                 SDL_Point fromRangey = {.x = 0, transform->canvH / 2};
//                 SDL_Point toRangex = {.x = 0, transform->canvW};
//                 SDL_Point toRangey = {.x = 0, transform->canvH};
//                 input.mouse.x = scaleNumber_toRange(input.mouse.x, fromRangex, toRangex);
//                 input.mouse.y = scaleNumber_toRange(input.mouse.y, fromRangey, toRangey);
//             }

//             if (transform->prevX == -1 && transform->prevY == -1)
//             {
//                 transform->prevX = input.mouse.x;
//                 transform->prevY = input.mouse.y;
//                 return 0;
//             }

//             if (input.mouse.x - transform->prevX == 0)
//             {
//                 slope = 0;
//                 stepAmount = 1;
//             }
//             else
//             {
//                 slope = (input.mouse.y - transform->prevY) / (input.mouse.x - transform->prevX);
//                 stepAmount = 1;
//             }
//             b = -(input.mouse.x * slope) + input.mouse.y;
//             stepDir = (input.mouse.x - transform->prevX > 0 ? 1 : -1);


//             for (int i = 0; i < stepAmount; i++)
//             {
//                 x = transform->prevX + (stepDir * i);
//                 y = x * slope + b;
//                 computeHough(x, y,
//                             transform->houghSpace, HOUGHSPACE_W, HOUGHSPACE_H);
//             }
//             SDL_SetRenderTarget(SDLX_Display_Get()->renderer, transform->drawSpace);
//             SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->prevX , transform->prevY, input.mouse.x, input.mouse.y);
//             SDL_SetRenderTarget(SDLX_Display_Get()->renderer, NULL);

//             transform->prevX = input.mouse.x;
//             transform->prevY = input.mouse.y;
//         }
//     }
//     else
//     {
//         transform->prevX = -1;
//         transform->prevY = -1;
//     }

//     SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
//     return 0;
// }
