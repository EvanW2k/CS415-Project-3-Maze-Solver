# CS415-Project-3
Authors: Evan Walters and Hanpei Zhang
Date: December 13th, 2023

- Everything appears to work fine, ran it on blue with the makefile. 
- The Main function uses threading and gives breadthFS and bestFS its own thread to save time.
- **Obstacles** are defined as any pixel with all RGB values less than 100.
  - Example: Red has RGB (255, 0, 0) this is not an obstacle as one of the values is > 100.
  - Black has RGB (0, 0, 0) all values are < 100 so it is an obstacle
 
- There are 2 test cases each with a reccommended start ***s***, and goal ***t*** in (col, row) format
    - *maze.bmp*   start pixel: (8, 8)   goal pixel: (202, 190)
    - *maze2.bmp*  start pixel: (0,0)    goal pixel: (78, 0)

<ins>Contributions:</ins>

Evan: breadth first search, threading in main, most of the extra functions

Hanpei: best first search, main

Both: testing, documentation
