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
// In: BMP image, starting pixel, terminate pixel, a distance to return
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
	vector<vector<bool>> visited (I.TellWidth(), vector<bool>(I.TellHeight(), false));
	// 2d previous vector of pixels, initalized to image size
	vector<vector<pixel>> previous(I.TellWidth(), vector<pixel>(I.TellHeight(), {-1, -1}));

	Q.push(s);
	visit(s, visited);

	while (!Q.empty() && !(isVisited(t, visited))) {
		pixel u = Q.front();
		Q.pop();

		// cout << "Looking at pixel: " << u.col << ", " << u.row << endl;

		vector<pixel> neighbors = getNeighbors(u, t, I);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (!isVisited(neighbors[i], visited)) {
				// visit, update dist, and color
				visit(neighbors[i], visited);
				makeGreen(neighbors[i], result);

				// set prev and push
				setPrev(neighbors[i], u, previous);
				Q.push(neighbors[i]);
			}
		}
	}

	dist = 1;
	pixel v = t;
	while (v != s) {
		dist++;
		makeRed(v, result);
		v = getPrev(v, previous);
	}

	// display starter and target pixels as pink
	makeBlue(s, result);
	makeBlue(t, result);

	return result;
}


//**********************************************************************
// Function: BestFirstSearch
// In: image, start pizel, terminate pixel, reference to int dist
// Return: BMP image, and dist from of path
// DESC: Like BReadthFirstSearch but instead uses a priority queue to
// determine which pixel ot check. The value is based on the distance
// a pixel is from t.
//**********************************************************************
BMP BestFirstSearch(BMP I, pixel s, pixel t, int& dist) {

	assert(!isObstacle(s, I));

    BMP result = I;

    priority_queue<pixelPriority> Q;

	// 2d visited bool vector initalized to image size with values = false
	vector<vector<bool>> visited(I.TellWidth(), vector<bool>(I.TellHeight(), false));
	// 2d distance vector, initalized to image size with values = integer max
	vector<vector<int>> distance(I.TellWidth(), vector<int>(I.TellHeight(), numeric_limits<int>::max()));
	// 2d previous vector of pixels, initalized to image size
	vector<vector<pixel>> previous(I.TellWidth(), vector<pixel>(I.TellHeight(), { -1, -1 }));

    visit(s, visited);
    setDist(s, h(s, t), distance);

    Q.push({s, h(s, t)});

    while (!Q.empty() && !(isVisited(t, visited))) {
        pixel u = Q.top().location;
        Q.pop();

		// cout << "Looking at pixel: " << u.col << ", " << u.row << endl;

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
	dist = 1;
    pixel v = t;
    while (v != s) {
		dist++;
        makeRed(v, result);
        v = getPrev(v, previous);
    }

    // display starter and target pixels as blue
    makeBlue(s, result);
    makeBlue(t, result);

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
	if (image(p.col, p.row)->Red > 100 || image(p.col, p.row)->Green > 100 || image(p.col, p.row)->Blue > 100) {
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
	visited[p.col][p.row] = true;
	return true;
}


//**********************************************************************
// Function: isVisited
// In: pixel, 2d vector of bools
// Return: visit status of pixel in terms of a bool
// DESC: Returns the visted value for the particular pixel.
//**********************************************************************
bool isVisited(pixel p, vector<vector<bool>> visited) {
	return visited[p.col][p.row];
}


//**********************************************************************
// Function: setDist
// In: pixel, dist value to set, 2d vector of bools
// Return: bool for completion
// DESC: sets the distance value for the pixel.
//**********************************************************************
bool setDist(pixel p, int dist, vector<vector<int>>& distance) {
	distance[p.col][p.row] = dist;
	return true;
}

//**********************************************************************
// Function: getDist
// In: pixel, 2d vector of ints
// Return: distance to pixel
// DESC: return dist value for pixel
//**********************************************************************
int getDist(pixel p, vector<vector<int>> distance) {
	return distance[p.col][p.row];
}

//**********************************************************************
// Function: setPrev
// In: pixel, the previous pixel, 2d vector of pixels
// Return: bool for completion
// DESC: sets the pixel's previous pixel.
//**********************************************************************
bool setPrev(pixel p, pixel prev_p, vector<vector<pixel>>& previous) {
	previous[p.col][p.row] = prev_p;
	return true;
}

//**********************************************************************
// Function: getPrev
// In: pixel, 2d vector of pixels
// Return: a pixel
// DESC: returns the pixel that is the current pixels previous
//**********************************************************************
pixel getPrev(pixel p, vector<vector<pixel>> previous) {
	assert(previous[p.col][p.row].col != -1);	// make sure there is a previous
	return previous[p.col][p.row];
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
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.col, p.row + 1 }, image))
			neighbors.push_back({ p.col, p.row + 1 });		// south neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.col + 1, p.row }, image))
			neighbors.push_back({ p.col + 1, p.row });		// east neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.col, p.row - 1 }, image))
			neighbors.push_back({ p.col, p.row - 1 });		// north neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.col - 1, p.row }, image))
			neighbors.push_back({ p.col - 1, p.row });		// west neighbor
	}
	// optimal neighbor order for t being up and right
	else if (p.col < t.col && p.row > t.row) {
		if (p.row - 1 >= 0 && !isObstacle({ p.col, p.row - 1 }, image))
			neighbors.push_back({ p.col, p.row - 1 });		// north neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.col + 1, p.row }, image))
			neighbors.push_back({ p.col + 1, p.row });		// east neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.col - 1, p.row }, image))
			neighbors.push_back({ p.col - 1, p.row });		// west neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.col, p.row + 1 }, image))
			neighbors.push_back({ p.col, p.row + 1 });		// south neighbor
	}
	// optimal neighbor order for t being up and left
	else if (p.col > t.col && p.row > t.row) {
		if (p.row - 1 >= 0 && !isObstacle({ p.col, p.row - 1 }, image))
			neighbors.push_back({ p.col, p.row - 1 });		// north neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.col - 1, p.row }, image))
			neighbors.push_back({ p.col - 1, p.row });		// west neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.col + 1, p.row }, image))
			neighbors.push_back({ p.col + 1, p.row });		// east neighbor
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.col, p.row + 1 }, image))
			neighbors.push_back({ p.col, p.row + 1 });		// south neighbor
	}
	// optimal neighbor order for t being down and left
	else {
		if (p.row + 1 < image.TellHeight() && !isObstacle({ p.col, p.row + 1 }, image))
			neighbors.push_back({ p.col, p.row + 1 });		// south neighbor
		if (p.col - 1 >= 0 && !isObstacle({ p.col - 1, p.row }, image))
			neighbors.push_back({ p.col - 1, p.row });		// west neighbor
		if (p.col + 1 < image.TellWidth() && !isObstacle({ p.col + 1, p.row }, image))
			neighbors.push_back({ p.col + 1, p.row });		// east neighbor
		if (p.row - 1 >= 0 && !isObstacle({ p.col, p.row - 1 }, image))
			neighbors.push_back({ p.col, p.row - 1 });		// north neighbor
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
	image(p.col, p.row)->Red = 0;
	image(p.col, p.row)->Green = 255;
	image(p.col, p.row)->Blue = 0;
	image(p.col, p.row)->Alpha = 0;
	return true;
}

//**********************************************************************
// Function: makeRed
// In: pixel, and image
// Return: bool for compeltion
// DESC: colors the pixel in the image Red
//**********************************************************************
bool makeRed(pixel p, BMP& image) {
	image(p.col, p.row)->Red = 255;
	image(p.col, p.row)->Green = 0;
	image(p.col, p.row)->Blue = 0;
	image(p.col, p.row)->Alpha = 0;
	return true;
}


//**********************************************************************
// Function: makeBlue
// In: pixel, and image
// Return: bool for compeltion
// DESC: colors the pixel in the image Blue
//**********************************************************************
bool makeBlue(pixel p, BMP& image) {
	image(p.col, p.row)->Red = 0;
	image(p.col, p.row)->Green = 0;
	image(p.col, p.row)->Blue = 255;
	image(p.col, p.row)->Alpha = 0;
	return true;
}


//**********************************************************************
// Function: h
// In: a pixel, and terminating pixel
// Return: distance form t
// DESC: uses pythagrum theorum to get distance from u to t.
//**********************************************************************
int h(pixel u, pixel t) {
	return abs(u.row - t.row) + abs(u.col - t.col);
}