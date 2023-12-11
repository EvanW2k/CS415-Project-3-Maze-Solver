//************************************************************************
// Assignment: CS415 - Project 3
// Evan Walters, Hanpei Zhang
// Date: Dec 10th, 2023
// Description:
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

	BreadthFirstSearch(image, s, t);
	if (!BreadthFirstSearch(image, s, t).WriteToFile(breadthFSOutputFileName.c_str())) {
		std::cerr << "Error writing to file " << breadthFSOutputFileName << std::endl;
		return 1;
	}

	BestFirstSearch(image, s, t);
	if (!BestFirstSearch(image, s, t).WriteToFile(bestFSOutputFileName.c_str())) {
		std::cerr << "Error writing to file " << bestFSOutputFileName << std::endl;
		return 1; 
	}

	RGBApixel temp = image.GetPixel(0, 0);
	cout << "Height is " << image.TellHeight() << " Width is " << image.TellWidth() << endl;
	cout << "Pixel 0,0 has Red: " << (int)temp.Red << " Green:" << (int)temp.Green << " Blue: " << (int)temp.Blue << endl;

	std::cout << "Breadth-First Search output saved to " << breadthFSOutputFileName << std::endl;
	std::cout << "Best-First Search output saved to " << bestFSOutputFileName << std::endl;

	return 0;
}
