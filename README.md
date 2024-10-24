# CS415-Project-3
Authors: Evan Walters and Hanpei Zhang
Date: December 13th, 2023

This project uses 2 methods to solve a maze (or more literally find a path from a start point ot an end point). 
The two methods are breadth first search and best first search (in the unweighted case).

The algorithm traverses a BMP image.

- The Main function uses threading and gives breadthFS and bestFS its own thread to save time.
- **Obstacles** are defined as any pixel with all RGB values less than 100.
  - Example: Red has RGB (255, 0, 0) this is not an obstacle as one of the values is > 100.
  - Black has RGB (0, 0, 0) all values are < 100 so it is an obstacle
- A new image is created showing the path each algorithm used.
- Everything appears to work fine, ran it on blue with the makefile.
 
- There are 2 test cases each with a recommended start ***s***, and goal ***t*** in (col, row) format
    - *maze.bmp*   start pixel: (8, 8)   goal pixel: (202, 190)
    - *maze2.bmp*  start pixel: (0, 0)    goal pixel: (78, 0)

<ins>Contributions:</ins>

Evan: breadth first search, threading in main, most of the extra functions

Hanpei: best first search, main

Both: testing, documentation
