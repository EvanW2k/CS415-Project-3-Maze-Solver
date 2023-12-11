//************************************************************************
// Assignment: Project 3
// Authors: Evan Walters and Hanpei Zhang
// Date: December 10th, 2023
// File: P3_helper.h
// 
// Description: Header file for all the function definitions 
// in P3_helper.cpp, saving up space in main.cpp
//************************************************************************



#ifndef P3_HELPER_H
#define P3_HELPER_H

#include <iostream>
#include <queue>
#include <vector>
#include <limits>	// for integer max
#include<cassert>
#include "EasyBMP.h"
using namespace std;

//************************************************************************
// Struct: pixel
// Houses coordinates for a pixel that can be used in conjunction with 
// the EasyBMP library. The struct also in clude an overload on the
// != operator.
//************************************************************************
struct pixel {
	int col = 0;
	int row = 0;
	
	// overload '!=' operator
	bool operator != (const pixel other) const {
		if (this->col != other.col)
			return true;
		else if (this->row != other.row)
			return true;

		return false;
	}
};

//************************************************************************
// Struct: pixelPriority
// Houses a pixel object and an assocaiated priority. Also has an 
// overload of the < operator so that prioirty_queue object use a min heap
// instead of max heap.
//************************************************************************
struct pixelPriority {
	pixel location;
	int priority;

	bool operator<(const pixelPriority& p) const {
		return priority > p.priority; 
	}
};

// Search functions
BMP BreadthFirstSearch(BMP I, pixel s, pixel t, int& dist);
BMP BestFirstSearch(BMP I, pixel s, pixel t, int& dist);

// obstacle function
bool isObstacle(pixel p, BMP image);	// obstacles are any pixels with all RGB values > 100

// visit functions
bool visit(pixel p, vector<vector<bool>>& visited);
bool isVisited(pixel p, vector<vector<bool>> visited);

// distance functions
bool setDist(pixel p, int dist, vector<vector<int>>& distance);
int getDist(pixel p, vector<vector<int>> distance);

// previous functions
bool setPrev(pixel p, pixel prev_p, vector<vector<pixel>>& previous);
pixel getPrev(pixel p, vector<vector<pixel>> previous);

// generate cardinal neighbors of a pixel
vector<pixel> getNeighbors(pixel p, pixel t, BMP image);

// modify a BMP image pixel
bool makeGreen(pixel p, BMP& image);
bool makeRed(pixel p, BMP& image);
bool makeBlue(pixel p, BMP& image);

// generate a disance value for priorities
int h(pixel u, pixel t);

#endif
