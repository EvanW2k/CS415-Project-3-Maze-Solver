//************************************************************************
// Assignment: CS415 - Project 3
// Evan Walters, Hanpei Zhang
// Date: Dec 10th, 2023
// Description: Takes and input BMP image, and the cordinates for a 
// starting pixel (s) and terminating pixel (t). Using BreadthFirstSearch 
// and BestFirstSearch a path from s to t is made and put on a resulting 
// BMP image. The path is marked in red and the visited pixels are green,
// also the s and t are marked as blue. The program also outputs the 
// distance of the paths.
//************************************************************************

#include <iostream>
#include "P3_helper.h"
using namespace std;

int main() {

	pixel s, t;

	cout << "Enter the row number of the starting pixel (s): ";
	cin >> s.row;
	cout << "Enter the column number of the starting pixel (s): ";
	cin >> s.col;
	cout << "Enter the row number of the goal pixel (t): ";
	cin >> t.row;
	cout << "Enter the column number of the goal pixel (t): ";
	cin >> t.col;

	BMP image;
	string inputFileName;
	string breadthFSOutputFileName;
	string bestFSOutputFileName;

	int breadthDist, bestDist;

	std::cout << "Please enter the name of the BMP file to read including .bmp: ";
	std::cin >> inputFileName;

	if (!image.ReadFromFile(inputFileName.c_str())) {
		std::cerr << "Error reading file " << inputFileName << std::endl;
		return 1;
	}

	std::cout << "Enter the name of the breadth first search output BMP file including .bmp: ";
	std::cin >> breadthFSOutputFileName;
	std::cout << "Enter the name of the best first search output BMP file including .bmp: ";
	std::cin >> bestFSOutputFileName;

	//BreadthFirstSearch(image, s, t, breadthDist);
	if (!BreadthFirstSearch(image, s, t, breadthDist).WriteToFile(breadthFSOutputFileName.c_str())) {
		std::cerr << "Error writing to file " << breadthFSOutputFileName << std::endl;
		return 1;
	}

	//BestFirstSearch(image, s, t, bestDist);
	if (!BestFirstSearch(image, s, t, bestDist).WriteToFile(bestFSOutputFileName.c_str())) {
		std::cerr << "Error writing to file " << bestFSOutputFileName << std::endl;
		return 1;
	}

	std::cout << "Breadth-First Search output saved to " << breadthFSOutputFileName << std::endl;
	std::cout << "Best-First Search output saved to " << bestFSOutputFileName << std::endl;

	std::cout << "Breadth-First Search distance: " << breadthDist << std::endl;
	std::cout << "Best-First Search distance " << bestDist << std::endl;

	return 0;
}