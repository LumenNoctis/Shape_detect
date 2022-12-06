# Edge Detection

## Overview

This is a computer vision program that is used to detect edges. The user will draw something and the program will attempt to find **straight edges** within the picture

This specific algorithm uses the hough transform to check for lines.


## Implementation

When a user draws, we capture the mouse input. Because knowing what pixels have been written to screen is an expensive operation in SDL2, we manually calcute the path of the mouse since the last input capture.

For each point in this path we calculate the hough transform. The hough transform works as follows:

For a given point P(x,y) we graph every line that may pass throught it. We use polar cooridnates to avoid issues with slopes and potential division by 0 when the line is vertical.

The formula for this line is x * cos(t) + y * sin(t) + d;

For a given point P(x,y) we graph every possible distance (d) from the origin (within a range) for every angle (t)

We graph all the points like this and then use a divide and conquer algorithm to find all the local maxmiums (above a certain threshold). Each of these maximums represent the distance and angle of an edge.


## Controls

````
[Tab] : Switch mode
[R] : Reset drawing
--------------------------
      Mode: Draw
[Left arrow] :
[Right arrow] :
Use the upper left corner to draw
--------------------------
    Mode: Visualizer
[Space] : Calculate edges / Return to drawing

````

## Compiling and running

This program uses SDL2 and assumes it is a system library.

SDL2 may be installed by default depending on your OS. It is available in most Linux package managers and via Brew for OSX
You may download it here https://wiki.libsdl.org/Installation

To use this program :
````
git clone https://github.com/LumenNoctis/Shape_detect/
cd Shape_detect
./draw
````
If you are on Linux chances are the executable will just work
Otherwise you may compile this yourself
```
make re
./draw
```

The current executable has been compiled on Arch Linux 5.15.55-2-lts. If compilation fails or the executable fails to run in your OS please let me know!
