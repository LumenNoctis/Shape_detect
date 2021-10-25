# include "rush.h"
# include "MT_vec2.h"

#define ERR_MARGIN 22
#define CMP_MARGIN 3
#define NPATTERNS 8
#define N_REPEAT_VALID 3
#define MIN_DELTA 1

typedef struct Stroke
{
	MT_Vector2 vec;
	SDL_Point start;
	SDL_Point end;
	double angle;
	int delta;
}				Stroke;

static Stroke match[NPATTERNS];

void test_levelInit(void *arg)
{

	SDL_Log("Init Test level\n");
	match[0].vec.x = 100;
	match[0].vec.y = 0;
	match[0].angle = MT_ToDegf(SDL_atan2f(match[0].vec.y, match[0].vec.x));

	match[1].vec.x = -100;
	match[1].vec.y = 0;
	match[1].angle = MT_ToDegf(SDL_atan2f(match[1].vec.y, match[1].vec.x));

	match[2].vec.x = 0;
	match[2].vec.y = 100;
	match[2].angle = MT_ToDegf(SDL_atan2f(match[2].vec.y, match[2].vec.x));

	match[3].vec.x = 0;
	match[3].vec.y = -100;
	match[3].angle =  MT_ToDegf(SDL_atan2f(match[3].vec.y, match[3].vec.x));

	match[4].vec.x = 50;
	match[4].vec.y = -50;
	match[4].angle =  MT_ToDegf(SDL_atan2f(match[4].vec.y, match[4].vec.x));

	match[5].vec.x = -50;
	match[5].vec.y = -50;
	match[5].angle =  MT_ToDegf(SDL_atan2f(match[5].vec.y, match[5].vec.x));

	match[6].vec.x = -50;
	match[6].vec.y = 50;
	match[6].angle = MT_ToDegf(SDL_atan2f(match[6].vec.y, match[6].vec.x));

	match[7].vec.x = 50;
	match[7].vec.y = 50;
	match[7].angle = MT_ToDegf(SDL_atan2f(match[7].vec.y, match[7].vec.x));

	// match[8].vec.x = 75;
	// match[8].vec.y = -25;
	// match[8].angle =  MT_ToDegf(SDL_atan2f(match[8].vec.y, match[8].vec.x));

	// match[9].vec.x = -75;
	// match[9].vec.y = -25;
	// match[9].angle =  MT_ToDegf(SDL_atan2f(match[9].vec.y, match[9].vec.x));

	// match[10].vec.x = -75;
	// match[10].vec.y = 25;
	// match[10].angle = MT_ToDegf(SDL_atan2f(match[10].vec.y, match[10].vec.x));

	// match[11].vec.x = 75;
	// match[11].vec.y = 25;
	// match[11].angle = MT_ToDegf(SDL_atan2f(match[11].vec.y, match[11].vec.x));

	// match[12].vec.x = 25;
	// match[12].vec.y = -75;
	// match[12].angle =  MT_ToDegf(SDL_atan2f(match[12].vec.y, match[12].vec.x));

	// match[13].vec.x = -25;
	// match[13].vec.y = -75;
	// match[13].angle =  MT_ToDegf(SDL_atan2f(match[13].vec.y, match[13].vec.x));

	// match[14].vec.x = -25;
	// match[14].vec.y = 75;
	// match[14].angle = MT_ToDegf(SDL_atan2f(match[14].vec.y, match[14].vec.x));

	// match[15].vec.x = 25;
	// match[15].vec.y = 75;
	// match[15].angle = MT_ToDegf(SDL_atan2f(match[15].vec.y, match[15].vec.x));

	for (int i = 0; i < NPATTERNS; i++)
		SDL_Log("Angles %d %f", i, match[i].angle);
}

int find(Stroke stroke)
{
	for (int x = 0; x < NPATTERNS; x++)
		{
			if (
				(stroke.angle <= match[x].angle + ERR_MARGIN &&
				stroke.angle >= match[x].angle - ERR_MARGIN)
			)
			{
			// SDL_Log("Attempt %d y: %d [ %d | %d ] \n");
				return x;
			}
		}
	return -1;
}

int sanitizeData(Stroke stroke[1000],Stroke (*san)[1000],  int amount)
{
	int i;
	int n;
	int x;
	double angle;
	int isDiff;
	int diff;
	Stroke processed[300];

	i = 0;
	n = 0;
	while (i < amount)
	{
		// if (stroke[i].delta == 0)
		// {
			while (i < amount && abs(stroke[i].delta) <= 3) {i++;}
			// processed[n].angle = stroke[i].angle;
			// angle = stroke[i].angle;
			// // if (n > 0)
			// // 	processed[n].angle = angle;
			// n++;
		// }
		processed[n].angle = stroke[i].angle;
		angle = stroke[i].angle;
			// if (n > 0)
			// 	processed[n].angle = angle;
			n++;
		i++;
	}
	if (i < amount && stroke[i].delta != 0)
		processed[n++].angle = angle;

	i = 0;
	diff = 0;
	angle = processed[i].angle;
	x = 0;
		while (i < n)
	{
		SDL_Log("Processed %f", processed[i].angle);
		i++;
	}
	i = 0;
	while (i < n)
	{
		// SDL_Log("Pass %d of %d", i , n);
		if (processed[i].angle == angle)
		{

			// SDL_Log("SAME %f", angle);
			diff++;
		}
		else
		{
			// SDL_Log("DIFF %d %f %f", diff, angle, processed[i].angle);
			if (diff >= N_REPEAT_VALID)
			{
				// SDL_Log("VALID %d %f", diff, angle);
				if (x == 0 || (*san)[x - 1].angle != angle)
				{
					(*san)[x].angle = angle;
					x++;
				}
			}
			diff = 1;
			angle = processed[i].angle;
		}
		i++;
	}
	if (diff >= N_REPEAT_VALID)
	{
		// SDL_Log("VALID %d %f", diff, angle);
		(*san)[x].angle = angle;
		x++;
	}
	return x;
}

void test_level(void *arg)
{
	static int isdown;
	static int i = -1;
	static int c;
	static int n;
	int aa;
	SDLX_Input input;
	static Stroke stroke[1000];
	static Stroke predictions[1000];
	static Stroke save;
	static Stroke cmp;
	Stroke san[1000];

	input = SDLX_InputGet();

	if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
	{
		i  = -1;
		if (!isdown)
		{
			n = 0;
			c = 0;
			isdown = SDLX_TRUE;
			stroke[n].start = input.mouse;
			stroke[n].end = input.mouse;
			aa= find(stroke[n]);
			SDL_Log("C %d", aa);
			if (aa < 0)
			{
				if (n > 0)
					predictions[n] = predictions[n - 1];
				else
					predictions[n] = match[0];
			}
			else
				predictions[n] = match[aa];
			SDL_Log("AAA ");
			n++;
		}
		else if (isdown == SDLX_NONE)
			isdown = SDLX_FALSE;
	}
	if (isdown == SDLX_TRUE)
	{
		save = stroke[n];
		stroke[n].end = input.mouse;
		stroke[n].start = stroke[n - 1].end;
		stroke[n].vec.x = stroke[n].end.x - stroke[n].start.x;
		stroke[n].vec.y = stroke[n].end.y - stroke[n].start.y;
		stroke[n].angle = MT_ToDegf(SDL_atan2f(stroke[n].vec.y, stroke[n].vec.x));

		aa = find(stroke[n]);
		if (aa < 0)
			{
				if (n > 0)
					predictions[n] = predictions[n - 1];
				else
					predictions[n] = match[0];
			}
			else
				predictions[n] = match[aa];
		predictions[n].delta = input.mouse_delta.x;
		if (input.mouse_delta.x == 0 && input.mouse_delta.y == 0)
			predictions[n].delta = 0;
		n++;
	}
	if (input.mouse_click == SDL_MOUSEBUTTONUP && isdown)
	{
		isdown = SDLX_NONE;
		// stroke[n].start = input.mouse;
		c = sanitizeData(predictions, &san, n);
		for (int _ = 0; _ < c; _++)
		{
			SDL_Log("Sanitized %f", san[_].angle);
		}
		for (int _ = 0; _ < n; _++)
		{
			SDL_Log("Drawn vector [%f] | Predicted [%f] [DELTA %d]", stroke[_].angle, predictions[_].angle, predictions[_].delta);
		}

		if (i == SDLX_NONE)
			SDL_Log("No correction found");
		else
			SDL_Log("Similar to stroke %d", i);
	}
	if (isdown == SDLX_NONE)
	{
		SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer,0, 255, 0, 255);
		for (int _ = 0; _ < n; _++)
		{
			SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke[_].start.x, stroke[_].start.y, stroke[_].start.x + predictions[_].vec.x,
																							stroke[_].start.y + predictions[_].vec.y);
		}
		SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer,0, 0, 255, 255);
		for (int _ = 0; _ < c; _++)
		{
			SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, 50 + (50 * _), 100, 50 + (50 * _) + match[find(san[_])].vec.x,
																							100 + match[find(san[_])].vec.y);
		}
	}

	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 255, 0, 0, 255);
	for (int x = 0; x < n; x++)
	{
		SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke[x].start.x, stroke[x].start.y, stroke[x].end.x, stroke[x].end.y);
	}

		// SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 255, 0, 0, 255);
	for (int x = 0; x < NPATTERNS; x++)
	{
		SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, WIN_W - 100, WIN_H - 100, (WIN_W - 100) + match[x].vec.x,(WIN_H - 100) + match[x].vec.y);
	}
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 0, 0, 0, 255);
}



void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	// SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
