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
#include <thread>	// to exec breadthFS and bestFS at same time
#include "P3_helper.h"
using namespace std;

int main() {

	pixel s, t;

	BMP image;

	string inputFileName;
	string breadthFSOutputFileName;
	string bestFSOutputFileName;

	int breadthDist, bestDist;


	// get coordinate inputs
	cout << "Enter the column number of the starting pixel (s): ";
	cin >> s.col;
	cout << "Enter the row number of the starting pixel (s): ";
	cin >> s.row;

	cout << "Enter the column number of the goal pixel (t): ";
	cin >> t.col;
	cout << "Enter the row number of the goal pixel (t): ";
	cin >> t.row;

	// input image file
	cout << "Please enter the name of the BMP file to read including .bmp: ";
	cin >> inputFileName;

	// copy file to BMP object
	if (!image.ReadFromFile(inputFileName.c_str())) {
		cerr << "Error reading file " << inputFileName << endl;
		return 1;
	}

	// cout << "Height: " << image.TellHeight() << " Width: " << image.TellWidth() << endl;
	// cout << "t color: " << (int) image(t.col, t.row)->Red << " " << (int) image(t.col, t.row)->Blue << " " << (int) image(t.col, t.row)->Green << endl;

	// output file names
	cout << "Enter the name of the breadth FS output file including .bmp: ";
	cin >> breadthFSOutputFileName;
	cout << "Enter the name of the best FS output file including .bmp: ";
	cin >> bestFSOutputFileName;




	cout << "Creating Output Images (this may take a minute)...\n";

	// threaded calls to breadthFS and bestFS function calls

	thread breadth_Thread{ [=, &breadthDist, &image]() {
		if (!BreadthFirstSearch(image, s, t, breadthDist).WriteToFile(breadthFSOutputFileName.c_str())) {
			cerr << "Error writing to file " << breadthFSOutputFileName << endl;
			return 1;
		}
		cout << "Breadth-First Search output saved to " << breadthFSOutputFileName << endl;

	} };


	thread best_Thread{ [=, &bestDist, &image]() {
		if (!BestFirstSearch(image, s, t, bestDist).WriteToFile(bestFSOutputFileName.c_str())) {
			cerr << "Error writing to file " << bestFSOutputFileName << endl;
			return 1;
		}
		cout << "Best-First Search output saved to " << bestFSOutputFileName << endl;

	} };
	breadth_Thread.join();
	best_Thread.join();

	cout << "Breadth-First distance: " << breadthDist << endl;
	cout << "Best-First distance: " << bestDist << endl;
	return 0;
}