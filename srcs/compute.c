
# include "main.h"


int computeHough( int x, int y, int *arr, int w, int h)
{
    int angle = 0;
    double theta;
    int d = 0;
    
    // Formula: x cos(theta) + y sin(theta) = d
    while (angle < w)
    {
        theta = (angle * M_PI) / 180;
        d = x * cos(theta) + y * sin(theta);
        if (d * w + angle >= 0 && d * w + angle < h * w)
        {
            arr[d * w + angle] += 1;
        }
        angle++;
    }
}

// This goes in a "cross" shape
// improvement could be to make it square
int getMax_inRange(int range, int *arr, int w, int arraySize, int pos)
{
    int row;
    int col;
    int maxPos;
    int tryPos;
    
    maxPos = pos;
    col = -range;
    while (col <= range)
    {
        row = -range;
        while (row <= range)
        {
            tryPos = pos + ((row * w) + col);
            if (tryPos >= 0 && tryPos < arraySize && arr[tryPos] > arr[maxPos])
                maxPos = tryPos;
            row++;
        }
        col++;
    }
    return maxPos;
}

int getLocalMax(int arrLen, int start, int w, int *arr)
{
    int i;
    int nextIndex;
    int newNext;

    i = start;
    if (i >= arrLen || i < 0)
        return 0;
    SDL_Log("Start here %d", start);
    nextIndex = i;
    while (1)
    {
        i = nextIndex;
        nextIndex = getMax_inRange(SEARCHRANGE, arr, w, arrLen, i);
        if (nextIndex == i)
            break ;
    }
    SDL_Log("DONE Max %d at %d", arr[nextIndex], nextIndex);
}

int divideNconquer(int w, int h, int *arr)
{
    int stepX;
    int stepY;
    int n;
    int i;
    int currX;
    int currY;
    
    SDL_Log("---------------------------------------------");
    stepX = w / DIVIDE_X;
    stepY = h / DIVIDE_Y;
    i = 0;
    while (i <= DIVIDE_X)
    {
        n = 0;
        while (n <= DIVIDE_Y)
        {
            getLocalMax(w * h, stepY * i * w + stepX * n, w, arr);
            n++;
        }
        i++;
    }
}

int compute(t_transform *transform)
{
    if (transform->stage)
    {
        divideNconquer(HOUGHSPACE_W, HOUGHSPACE_H, transform->houghSpace);
        // Get lines
        // Call renderLinesBound
    }
    else
        renderDrawSpace(transform);
}