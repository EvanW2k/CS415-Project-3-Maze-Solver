//************************************************************************
// Assignment: Project 3
// Authors: Evan Walters and Hanpei Zhang
// Date: Dec 10th, 2023
// File: P3_helper.cpp
// 
// Description: Has all the function definitions for P3_helper.h
//************************************************************************

#include "P3_helper.h"

//**********************************************************************
// Function: BreadthFirstSearch
// In: BMP image, starting pixel, ending pixel, a distance to return
// Return: Distance from s to t, and the result BMP image
// DESC: From the starting pixel searches all neighbors for pixel t,
// adding them to a queue, then searching the next pixel in the queue 
// and their neighbors. Eventually t is found and the pathis traced 
// back. The distance from s to t is also returned by reference.
//**********************************************************************
BMP BreadthFirstSearch(BMP I, pixel s, pixel t, int& dist) {
	
	assert(!isObstacle(s, I));

	BMP result = I;

	const int numPixels = I.TellWidth() * I.TellHeight();

	queue<pixel> Q;

	// 2d visited bool vector initalized to image size with values = false
	vector<vector<bool>> visited (I.TellHeight(), vector<bool>(I.TellWidth(), false));
	// 2d distance vector, initalized to image size with values = integer max
	vector<vector<int>> distance(I.TellHeight(), vector<int>(I.TellWidth(), numeric_limits<int>::max()));
	// 2d previous vector of pixels, initalized to image size
	vector<vector<pixel>> previous(I.TellHeight(), vector<pixel>(I.TellWidth(), {-1, -1}));

	Q.push(s);
	visit(s, visited);
	setDist(s, 0, distance);

	while (!Q.empty() && !(isVisited(t, visited))) {
		pixel u = Q.front();
		Q.pop();

		vector<pixel> neighbors = getNeighbors(u, t, I);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (!isVisited(neighbors[i], visited)) {
				// visit, update dist, and color
				visit(neighbors[i], visited);
				makeGreen(neighbors[i], result);
				setDist(neighbors[i], getDist(u, distance) + 1, distance);

				// set prev and push
				setPrev(neighbors[i], u, previous);
				Q.push(neighbors[i]);
			}
		}
	}

	pixel v = t;
	while (v != s) {
		makeRed(v, result);
		v = getPrev(v, previous);
	}

	// display starter and target pixels as pink
	makeBlue(s, result);
	makeBlue(t, result);

	// edit distance which is passed by reference
	dist = getDist(t, distance);
	return result;
}


//**********************************************************************
// Function: BestFirstSearch
// In: BMP image, starting pixel, ending pixel, a distance to return
// Return: Distance from s to t, and the result BMP image
// DESC: Seeks the shortest path from a start pixel s to a target pixel t in an image. 
// It employs a heuristic to prioritize nearer pixels to t, using a priority queue 
// for efficient exploration. Once t is found, the path from s to t is traced back 
// and marked, and the path length is returned by reference."
//**********************************************************************
BMP BestFirstSearch(BMP I, pixel s, pixel t, int& dist) {

	assert(!isObstacle(s, I));

    BMP result = I;

    priority_queue<pixelPriority> Q;

    vector<vector<bool>> visited (I.TellHeight(), vector<bool>(I.TellWidth(), false));
    vector<vector<int>> distance(I.TellHeight(), vector<int>(I.TellWidth(), numeric_limits<int>::max()));
    vector<vector<pixel>> previous(I.TellHeight(), vector<pixel>(I.TellWidth(), { -1, -1 }));

    visit(s, visited);
    setDist(s, h(s, t), distance);

    Q.push({s, h(s, t)});

    while (!Q.empty() && !(isVisited(t, visited))) {
        pixel u = Q.top().location;
        Q.pop();


        vector<pixel> neighbors = getNeighbors(u, t, I);
        for (int i = 0; i < neighbors.size(); ++i) {
            if (!isVisited(neighbors[i], visited)) {
				// visit and color
                visit(neighbors[i], visited);
				makeGreen(neighbors[i], result);
				// set dist and prev then push
                int newDist = getDist(u, distance) + 1;
                setDist(neighbors[i], newDist, distance);
                setPrev(neighbors[i], u, previous);
                Q.push({neighbors[i], newDist + h(neighbors[i], t)});
            }
        }
    }

    pixel v = t;
    while (v != s) {
        makeRed(v, result);
        v = getPrev(v, previous);
    }

    // display starter and target pixels as blue
    makeBlue(s, result);
    makeBlue(t, result);

	// edit distance which is passed by reference
	dist = getDist(t, distance); // divide by 2 to make up for change 'h' function did
	return result;
}


//**********************************************************************
// Function: isObstacle
// In: pixel, and image with pixel
// Return: a bool based if location is within rgb range of an obstacle
// DESC: Determines if the pixel in the image is an obstacle, obstacles
// are any pixel with all RGB values below 100.
//**********************************************************************
bool isObstacle(pixel p, BMP image) {
	if (image(p.row, p.col)->Red > 100 || image(p.row, p.col)->Green > 100 || image(p.row, p.col)->Blue > 100) {
		return false;
	}
	return true;
}


//**********************************************************************
// Function: visit
// In: pixel, 2d vector of bools
// Return: bool for completion
// DESC: switched the pixel to visited
//**********************************************************************
bool visit(pixel p, vector<vector<bool>>& visited) {
	visited[p.row][p.col] = true;
	return true;
}


//**********************************************************************
// Function: isVisited
// In: pixel, 2d vector of bools
// Return: visit status of pixel in terms of a bool
// DESC: Returns the visted value for the particular pixel.
//**********************************************************************
bool isVisited(pixel p, vector<vector<bool>>& visited) {
	return visited[p.row][p.col];
}


//**********************************************************************
// Function: setDist
// In: pixel, dist value to set, 2d vector of bools
// Return: bool for completion
// DESC: sets the distance value for the pixel.
//**********************************************************************
bool setDist(pixel p, int dist, vector<vector<int>>& distance) {
	distance[p.row][p.col] = dist;
	return true;
}

//**********************************************************************
// Function: getDist
// In: pixel, 2d vector of ints
// Return: distance to pixel
// DESC: return dist value for pixel
//**********************************************************************
int getDist(pixel p, vector<vector<int>> distance) {
	return distance[p.row][p.col];
}

//**********************************************************************
// Function: setPrev
// In: pixel, the previous pixel, 2d vector of pixels
// Return: bool for completion
// DESC: sets the pixel's previous pixel.
//**********************************************************************
bool setPrev(pixel p, pixel prev_p, vector<vector<pixel>>& previous) {
	previous[p.row][p.col] = prev_p;
	return true;
}

//**********************************************************************
// Function: getPrev
// In: pixel, 2d vector of pixels
// Return: a pixel
// DESC: returns the pixel that is the current pixels previous
//**********************************************************************
pixel getPrev(pixel p, vector<vector<pixel>> previous) {
	assert(previous[p.row][p.col].row != -1);	// make sure there is a previous
	return previous[p.row][p.col];
}


//**********************************************************************
// Function: getNeighbors
// In: pixel, terminating pixel, and the image
// Return: a vector of pixels
// DESC: Returns all the neighbors of the pixel in a vector. Depending
// on which direction t is from the pixel, the order of the neighbors
// vary.
//**********************************************************************
vector<pixel> getNeighbors(pixel p, pixel t, BMP image) {
	vector<pixel> neighbors;

	// optimal neighbor order for t being down and right
	if (p.col <= t.col && p.row <= t.row) {
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.row, p.col + 1 }, image))
			neighbors.push_back({ p.row, p.col + 1 });		// east neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.row + 1, p.col }, image))
			neighbors.push_back({ p.row + 1, p.col });		// south neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.row, p.col - 1 }, image))
			neighbors.push_back({ p.row, p.col - 1 });		// west neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.row - 1, p.col }, image))
			neighbors.push_back({ p.row - 1, p.col });		// north neighbor
	}
	// optimal neighbor order for t being up and right
	else if (p.col < t.col && p.row > t.row) {
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.row, p.col + 1 }, image))
			neighbors.push_back({ p.row, p.col + 1 });		// east neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.row - 1, p.col }, image))
			neighbors.push_back({ p.row - 1, p.col });		// north neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.row, p.col - 1 }, image))
			neighbors.push_back({ p.row, p.col - 1 });		// west neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.row + 1, p.col }, image))
			neighbors.push_back({ p.row + 1, p.col });		// south neighbor
	}
	// optimal neighbor order for t being up and left
	else if (p.col > t.col && p.row > t.row) {
		if (p.col - 1 >= 0 && !isObstacle({ p.row, p.col - 1 }, image))
			neighbors.push_back({ p.row, p.col - 1 });		// west neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.row - 1, p.col }, image))
			neighbors.push_back({ p.row - 1, p.col });		// north neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.row, p.col + 1 }, image))
			neighbors.push_back({ p.row, p.col + 1 });		// east neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.row + 1, p.col }, image))
			neighbors.push_back({ p.row + 1, p.col });		// south neighbor
	}
	// optimal neighbor order for t being down and left
	else {
		if (p.col - 1 >= 0 && !isObstacle({ p.row, p.col - 1 }, image))
			neighbors.push_back({ p.row, p.col - 1 });		// west neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.row + 1, p.col }, image))
			neighbors.push_back({ p.row + 1, p.col });		// south neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.row, p.col + 1 }, image))
			neighbors.push_back({ p.row, p.col + 1 });		// east neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.row - 1, p.col }, image))
			neighbors.push_back({ p.row - 1, p.col });		// north neighbor
	}


	return neighbors;
}


//**********************************************************************
// Function: makeGreen
// In: pixel, and image
// Return: bool for ocmpeltion
// DESC: colors the pixel in the image green
//**********************************************************************
bool makeGreen(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 0;
	image(p.row, p.col)->Green = 255;
	image(p.row, p.col)->Blue = 0;
	image(p.row, p.col)->Alpha = 0;
	return true;
}

//**********************************************************************
// Function: makeRed
// In: pixel, and image
// Return: bool for compeltion
// DESC: colors the pixel in the image Red
//**********************************************************************
bool makeRed(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 255;
	image(p.row, p.col)->Green = 0;
	image(p.row, p.col)->Blue = 0;
	image(p.row, p.col)->Alpha = 0;
	return true;
}


//**********************************************************************
// Function: makeBlue
// In: pixel, and image
// Return: bool for compeltion
// DESC: colors the pixel in the image Blue
//**********************************************************************
bool makeBlue(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 0;
	image(p.row, p.col)->Green = 0;
	image(p.row, p.col)->Blue = 255;
	image(p.row, p.col)->Alpha = 0;
	return true;
}


//**********************************************************************
// Function: 
// In: 
// Return: b
// DESC: 
//**********************************************************************
int h(pixel u, pixel t) {
	return abs(u.row - t.row) + abs(u.col - t.col);
}
