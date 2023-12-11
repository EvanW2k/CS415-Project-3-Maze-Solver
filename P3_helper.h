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

struct pixel {
	int row = 0;
	int col = 0;
	
	// overload '!=' operator
	bool operator != (const pixel other) const {
		if (this->row != other.row)
			return true;
		else if (this->col != other.col)
			return true;

		return false;
	}
};

struct pixelPriority {
	pixel location;
	int priority;

	bool operator<(const pixelPriority& p) const {
		return priority > p.priority; 
	}
};


BMP BreadthFirstSearch(BMP I, pixel s, pixel t, int& dist);
BMP BestFirstSearch(BMP I, pixel s, pixel t, int& dist);

bool isObstacle(pixel p, BMP image);

bool visit(pixel p, vector<vector<bool>>& visited);
bool isVisited(pixel p, vector<vector<bool>>& visited);

bool setDist(pixel p, int dist, vector<vector<int>>& distance);
int getDist(pixel p, vector<vector<int>> distance);

bool setPrev(pixel p, pixel prev_p, vector<vector<pixel>>& previous);
pixel getPrev(pixel p, vector<vector<pixel>> previous);

vector<pixel> getNeighbors(pixel p, pixel t, BMP image);

bool makeGreen(pixel p, BMP& image);
bool makeRed(pixel p, BMP& image);
bool makeBlue(pixel p, BMP& image);

int h(pixel u, pixel t);

#endif
