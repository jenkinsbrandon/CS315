// CS 375 Exercise 6
//Brandon Jenkins
//Draws an XY axis and connects the same numbers to eachother

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

struct Point
{
	Point ();
	Point (float X, float Y);
	friend istream & operator >> (istream & ins, Point & P);
	friend ostream & operator << (ostream & point, const Point & P);
	float x;
	float y;
};
//THis function takes the 2 vectors of points and uses them to draw a line to "connect the dots"
void calcLines(ostream & outs, const vector<Point> & PV1, const vector<Point> & PV2, std::string color);
//actually draws the line
void connectDots (ostream & outs, Point pt1, Point pt2, std::string color);
//calculates the points on the axis
void calcPts (Point pt1, Point pt2, int num, vector <Point> & PV);

//calculation the interseciton of 2 liens using matrix determinants with the line points
//returns an array of points
vector<Point> calcIntersections(ostream & outs, const vector<Point> & PV1, const vector<Point> & PV2, std::string color);

//connects the above intersection with a line
void intersectionDotLines(ostream & outs, const vector<Point> & PV, std::string color);

//writes the initial head of the svg
void writeHead (ofstream & outs);
//writes the endof the svg
void writeTail (ofstream & outs);
//finds the points on the axis based on the number specified
void writePts (ostream & outs, const vector<Point> & PV);
//draws the line for the axis
void writeLine (ostream & outs, Point pt1, Point pt2, std::string color);
//draws the points
void writeCircle (ostream & outs, Point center, float radius, std::string color);
//labels the numbers on the axis
void writeText (ostream & outs, Point where, string text);




int main ()
{
	string filename;
	cout << "Enter output file name: ";
	cin >> filename;
	if (filename.length() < 5 || filename.substr(filename.length()-4) != ".svg")
		filename += ".svg";
	Point p1, p2, p3;
	int numpts;
	cout << "Enter point 1 (x and y should be positive, <= 1000, and separated by a comma): ";
	cin >> p1;
	cout << "Enter point 2 (x and y should be positive, <= 1000, and separated by a comma): ";
	cin >> p2;
	cout << "Enter point 3 (x and y should be positive, <= 1000, and separated by a comma): ";
	cin >> p3;
	cout << "Enter the number of points on each line: ";
	cin >> numpts;


	
	vector <Point> Pts1, Pts2;

	calcPts (p1, p2, numpts, Pts1);
	calcPts (p2, p3, numpts, Pts2);

	ofstream output (filename.c_str());
	
	writeHead (output);
	
	writeLine (output, p1, p2, "blue");
	writeLine (output, p2, p3, "blue");
	writePts (output, Pts1);
	writePts (output, Pts2);

	calcLines(output, Pts1, Pts2, "orange");

	intersectionDotLines(output, calcIntersections(output, Pts1, Pts2, "blue"), "purple");

	writeTail (output);
	output.close();
	return 0;
}

void calcPts (Point pt1, Point pt2, int num, vector <Point> & PV)
{
	float dx = (pt2.x - pt1.x) / num;
	float dy = (pt2.y - pt1.y) / num;

	for (int i = 0; i <= num; i++)
		PV.push_back (Point (pt1.x + i*dx, pt1.y + i*dy));
}

void writePts (ostream & outs, const vector<Point> & PV)
{
	for (int i = 1; i < PV.size()-1; i++)
	{
		writeCircle (outs, PV[i], 2, "red");
		//std::printf("Pt: %4.2f %4.2f \n", PV.at(i).x, PV.at(i).y);
		stringstream ss;
		ss << i;
		writeText (outs, Point(PV[i].x+2, PV[i].y+8), ss.str());
	}
}

void calcLines(ostream & outs, const vector<Point> & PV1, const vector<Point> & PV2, std::string color)
{

	for (int i = 1; i < PV1.size()-1; i++)
	{
		connectDots (outs, PV1.at(i), PV2.at(i), color);
		//std::printf("Pt: %4.2f %4.2f \n", PV1.at(i).x, PV1.at(i).y);
		//std::printf("Pt: %4.2f %4.2f \n\n", PV2.at(i).x, PV2.at(i).y);
	}
	
}

void intersectionDotLines(ostream & outs, const vector<Point> & PV, std::string color)
{

	for (int i = 0; i < PV.size()-1; i++)
	{
		connectDots (outs, PV.at(i), PV.at(i+1), color);
		//std::printf("Pt: %4.2f %4.2f \n", PV1.at(i).x, PV1.at(i).y);
		//std::printf("Pt: %4.2f %4.2f \n\n", PV2.at(i).x, PV2.at(i).y);
	}
	
}

vector<Point> calcIntersections(ostream & outs, const vector<Point> & PV1, const vector<Point> & PV2, std::string color)
{
	vector <Point> intersectionPts;
	for (int i = 1; i < PV1.size()-2; i++)
	{
		//first line
		float a1 = PV2.at(i).y - PV1.at(i).y;
		float b1 = PV1.at(i).x - PV2.at(i).x;
		float c1 = a1 * PV1.at(i).x + b1 * PV1.at(i).y;

		//next line
		float a2 = PV2.at(i+1).y - PV1.at(i+1).y;
		float b2 = PV1.at(i+1).x - PV2.at(i+1).x;
		float c2 = a2 * PV1.at(i+1).x + b2 * PV1.at(i+1).y;

		float det = a1*b2 - a2*b1;

		float tempx = (b2*c1 - b1*c2)/det; 
        float tempy = (a1*c2 - a2*c1)/det; 

        //printf("Pt:  %4.2f %4.2f \n",tempx,tempy);
        intersectionPts.push_back(Point(tempx,tempy));

        writeCircle (outs, Point(tempx,tempy), 2, color);

	}
	return intersectionPts;
}

void writeHead (ofstream & outs)
{
	outs << "<svg version=\"1.1\"" << endl;
		outs << "\tbaseProfile=\"full\"" << endl;
		outs << "\twidth=\"1000\" height=\"1000\"" << endl;
		outs << "\txmlns=\"http://www.w3.org/2000/svg\" >" << endl;
}

void writeTail (ofstream & outs)
{
	outs << "</svg>" << endl;
}

void writeLine (ostream & outs, Point pt1, Point pt2, std::string color)
{
	outs << "<line x1=\"" << pt1.x << "\" y1=\"" << pt1.y << "\""; 
	outs << " x2=\"" << pt2.x << "\" y2=\"" << pt2.y << "\" stroke=\""<< color <<"\"/>\n"; 
}

void writeCircle (ostream & outs, Point center, float radius, std::string color)
{
	outs << "<circle cx=\"" << center.x << "\" cy=\"" << center.y << "\""; 
	outs << " r=\"" << radius << "\" stroke=\""<< color <<"\"/>\n"; 
}

void writeText (ostream & outs, Point where, string text)
{
	outs << "<text x=\"" << where.x << "\" y=\"" << where.y << "\" style=\"font-family: sans-serif; font-size: 8pt;\">" << text << "</text>\n";
}

void connectDots (ostream & outs, Point pt1, Point pt2, std::string color)
{
	outs << "<line x1=\"" << pt1.x << "\" y1=\"" << pt1.y << "\""; 
	outs << " x2=\"" << pt2.x << "\" y2=\"" << pt2.y << "\" stroke=\""<< color <<"\"/>\n"; 
}

Point::Point ()
{
	x = y = 0;
}

Point::Point (float X, float Y)
{
	x = X;
	y = Y;
}

istream & operator >> (istream & ins, Point & P)
{
	char comma;
	ins >> P.x >> comma >> P.y;
	return ins;
}

ostream & operator << (ostream & outs, const Point & P)
{
	outs << P.x << ',' << P.y;
	return outs;
}
