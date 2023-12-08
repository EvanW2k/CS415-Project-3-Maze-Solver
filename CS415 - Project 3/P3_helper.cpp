//************************************************************************
// Assignment: Project 3
// Authors: Evan Walters and Hanpei Zhang
// Date: Dec 10th, 2023
// File: P3_helper.cpp
// 
// Description: Has all the function definitions outside of the main file.
//************************************************************************

#include "P3_helper.h"




BMP BreadthFirstSearch(BMP I, pixel s, pixel t) {
	
	assert(!isObstacle(s, I));

	BMP result = I;

	const int numPixels = I.TellWidth() * I.TellHeight();

	queue<pixel> Q;

	// 2d visited bool vector initalized to image size with values = false
	vector<vector<bool>> visited (I.TellHeight(), vector<bool>(I.TellWidth(), false));
	// 2d distance vector, initalized to image size with values = integer max
	vector<vector<int>> distance(I.TellHeight(), vector<int>(I.TellWidth(), numeric_limits<int>::max()));
	// 2d previous vector of pixels, initalized to image size
	vector<vector<pixel>> previous(I.TellHeight(), vector<pixel>(I.TellWidth()));

	Q.push(s);
	visit(s, visited);
	setDist(s, 0, distance);

	while (!Q.empty() && !(isVisited(t, visited))) {
		pixel u = Q.front();
		Q.pop();

		vector<pixel> neighbors = getNeighbors(u, I);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (!isVisited(neighbors[i], visited)) {
				visit(neighbors[i], visited);
				makeGreen(neighbors[i], result);
				setDist(neighbors[i], getDist(u, distance) + 1, distance);
				Q.push(neighbors[i]);
				setPrev(neighbors[i], u, previous);
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
	
	return result;
}



BMP BestFirstSearch(BMP I, pixel s, pixel t) {

	return I;
}

bool isObstacle(pixel p, BMP image) {
	if (image(p.row, p.col)->Red > 100 || image(p.row, p.col)->Green > 100 || image(p.row, p.col)->Blue > 100) {
		return false;
	}
	return true;
}

bool visit(pixel p, vector<vector<bool>>& visited) {
	visited[p.row][p.col] = true;
	return true;
}

bool isVisited(pixel p, vector<vector<bool>>& visited) {
	return visited[p.row][p.col];
}

bool setDist(pixel p, int dist, vector<vector<int>>& distance) {
	distance[p.row][p.col] = dist;
	return true;
}

int getDist(pixel p, vector<vector<int>> distance) {
	return distance[p.row][p.col];
}

bool setPrev(pixel p, pixel prev_p, vector<vector<pixel>>& previous) {
	previous[p.row][p.col] = prev_p;
	return true;
}

pixel getPrev(pixel p, vector<vector<pixel>> previous) {
	return previous[p.row][p.col];
}

vector<pixel> getNeighbors(pixel p, BMP image) {
	vector<pixel> neighbors;

	if (p.col - 1 >= 0 && !isObstacle({ p.row, p.col - 1 }, image))
		neighbors.push_back({ p.row, p.col - 1 });		// west neighbor
	if (p.col + 1 < image.TellWidth() && !isObstacle({ p.row, p.col + 1 }, image))
		neighbors.push_back({ p.row, p.col + 1 });		// east neighbor
	if (p.row - 1 >= 0 && !isObstacle({ p.row - 1, p.col }, image))
		neighbors.push_back({ p.row - 1, p.col });		// north neighbor
	if (p.row + 1 < image.TellHeight() && !isObstacle({ p.row + 1, p.col }, image))
		neighbors.push_back({ p.row + 1, p.col });		// south neighbor

	return neighbors;
}

bool makeGreen(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 0;
	image(p.row, p.col)->Green = 255;
	image(p.row, p.col)->Blue = 0;
	image(p.row, p.col)->Alpha = 0;
	return true;
}

bool makeRed(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 255;
	image(p.row, p.col)->Green = 0;
	image(p.row, p.col)->Blue = 0;
	image(p.row, p.col)->Alpha = 0;
	return true;
}

bool makeBlue(pixel p, BMP& image) {
	image(p.row, p.col)->Red = 0;
	image(p.row, p.col)->Green = 0;
	image(p.row, p.col)->Blue = 255;
	image(p.row, p.col)->Alpha = 0;
	return true;
}