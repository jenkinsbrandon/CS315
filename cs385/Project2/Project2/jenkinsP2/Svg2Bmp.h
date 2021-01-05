#pragma once
#include <iostream>
#include <vector>
#include "Bitmap_Image.hpp"

using namespace std;

class Svg2Bmp
{
    public:
	Svg2Bmp ();
	Svg2Bmp (const string & svgName, const string & expName);
	~Svg2Bmp ();

	struct Point
	{
		Point ();
		Point (double X, double Y);
		friend double dist (const Point & P1, const Point & P2);
		Point operator += (const Point & P);
		friend istream & operator >> (istream & ins, Point & P);
		friend ostream & operator << (ostream & outs, const Point & P);
		double x;
		double y;
	};

	struct Color
	{
		Color ();
		Color (string n);
		Color (string n, int r, int g, int b);
		friend ostream & operator << (ostream & outs, const Color & C);
		string name;
		int red, green, blue;
	};

	struct LineSeg
	{
		LineSeg ();
		LineSeg (const Point & P1, const Point & P2);
		bool operator < (const LineSeg & LS) const;
		double xIntercept (double y);
		friend ostream & operator << (ostream & outs, const LineSeg & LS);
		Point p1, p2;
		int y1, y2;
		double m, b;
	};

    private:
	ifstream svgFile;
	string bmpName;
	bitmap_image bmp;
	bitmap_image fillBmp;

	struct TransformElement
	{
		TransformElement ();
		TransformElement (char t);
		char eType;
		vector <double> values;
	};

	struct PathElement
	{
		PathElement ();
		PathElement (char t);
		char eType;
		vector <Point> points;
	};

	void ClearAttr ();
	void Attribute (const string & str);
	void ReportAttributes (string eType);
	double nValue (const string & str);
	double nValue (const string & str, int base);
	string sValue (const string & str);
	void String2Transformations (const string & t);
	void String2Path (const string & d);
	bool combine (LineSeg & ls1, const LineSeg & ls2);
	vector <Point> getFillPoints ();
	void Path ();

	int svgHeight;
	int svgWidth;
	Color fill;
	Color stroke;
	double stroke_width;
	double x1;
	double y1;
	double x2;
	double y2;
	double cx;
	double cy;
	double r;
	double x;
	double y;
	double height;
	double width;
	double rx;
	double ry;
	string points;
	string d;
	string style;
	string transform;
	vector <TransformElement> transformations;
	vector <PathElement> path;
	vector <LineSeg> lineSegs;

// From: Svg2Bmp.hh
// Project: CS 375 Project 1
// Author: Dr. Watts
// Description: This section contains the additional private variables
// and function prototypes added to the Svg2Bmp class for Project 1. 

    private:
	Point getRPoint (double t, Point p1, Point p2);
	void drawLine (bitmap_image & bmp, Point p1, Point p2, int red, int green, int blue, int width);
	void drawCurve (bitmap_image & bmp, Point p1, Point p2, Point p3, int red, int green, int blue, int width);
	void drawCurve (bitmap_image & bmp, Point p1, Point p2, Point p3, Point p4, int red, int green, int blue, int width);
	void drawPath (bitmap_image & bmp, vector <PathElement> & path, int red, int green, int blue, int width);
	void Line ();
	void Rect ();
	void Circle ();
	void Ellipse ();
	void Polygon ();
	void Polyline ();

#include "Svg2Bmp.hh"
};
