// File: Svg2Bmp.hh
// Project: CS 375 Project 2
// Author: 
// Description: This file contains additional private variables
//	and function prototypes for the Svg2Bmp class 

#define VERBOSE true

	void fillPath (bitmap_image & bmp,  int red, int green, int blue);
	void Fill (bitmap_image & bmp, int currentX, int currentY, int fillRed, int fillGreen, int fillBlue, vector<Point> & colorThese);
	void transformPath ();
