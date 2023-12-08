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

	pixel s = { 0, 0 };
	pixel t = { 863, 1535 };

	BMP image;
	image.ReadFromFile("test.bmp");


	RGBApixel temp = image.GetPixel(0, 0);
	cout << "Height is " << image.TellHeight() << " Width is " << image.TellWidth() << endl;
	cout << "Pixel 0,0 has Red: " << (int) temp.Red << " Greem:" << (int) temp.Green << " Blue: " << (int) temp.Blue << endl;

	BreadthFirstSearch(image, s, t).WriteToFile("test_result.bmp");


	return 0;
}