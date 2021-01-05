// CS 375 Exercise 6 b
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
vector<Point> calcRatio( ostream & outs,const vector<Point> & PV, string color );

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

//void readControlPoints( const vector<Point> & PV, vector <string> LV, int num );




int main (int argc, char *argv[])
{
	string inputFile = argv[1];
	string filename;
	cout << "Name of the input file: "<< inputFile<< endl;

	for(int i = 0; inputFile[i] != '.'; i++)
 	{
 		filename.push_back( inputFile[i] );
 	}
 	filename = filename + ".svg";

 	cout<<"Name of the output file: "<< filename <<endl;

	Point p1, p2, p3;
	int numpts;
	int controlPoints;
	string color1 = "black";
	string color2 = "blue";
	string color3 = "red";

	
	vector<string> lines;
	ifstream myfile (inputFile);
	if (myfile.is_open())
  	{
  		string s;
	    for( int i = 0; getline (myfile,s); ++i )
	    {
	       lines.push_back(s);
	    }
    	myfile.close();
  	}

  	bool delimited = false;
  	string tempNumPts;
  	string tempCntrlPts;
  	for( int i = 0; i < lines.at(0).size(); i ++ )
  	{
  		//cout << delimited << endl;
  		if( lines.at(0)[i] == ' ')
  		{
  			delimited = true;
  		}

  		else if(!delimited)
  		{
  			tempCntrlPts.push_back(lines.at(0)[i]);
  		}
  		else if(delimited)
  		{
  			tempNumPts.push_back(lines.at(0)[i]);
  		}
  		else 
  		{
  			cout << "Error in formatting number of control points and number of divisions!"<<endl;
  			exit(1);
  		}
  	}
  	numpts = atoi(tempNumPts.c_str());
  	controlPoints = atoi(tempCntrlPts.c_str());

  	cout << "Number of points:" << numpts << endl;
  	cout << "Number of control points: " << controlPoints << endl;

	vector <Point> vectOfCntrlPts;

	cout << "Control Points: " << endl;
	for( int j = 1; j <= controlPoints; j++)
  	{
  		bool delimited = false;
  		string tempX;
  		string tempY;
  		for( int i = 0; i < lines.at(j).size(); i ++ )
  		{
	  		
	  		if( lines.at(j)[i] == ',' || lines.at(j)[i] == ' ')	{ delimited = true; }

	  		else if(!delimited)	{ tempX.push_back(lines.at(j)[i]); }

	  		else if(delimited)	{ tempY.push_back(lines.at(j)[i]); }

	  		else 
	  		{
	  			cout << "Error in formatting control points!"<<endl;
	  			exit(1);
  			}
  		}

  		
  		vectOfCntrlPts.push_back( Point( atoi(tempX.c_str()), atoi(tempY.c_str()) ));

 	}
 	p1 = vectOfCntrlPts.at(0);
 	cout << p1.x << ',' << p1.y << endl;
 	p2 = vectOfCntrlPts.at(1);
 	cout << p2.x << ',' << p2.y << endl;
 	p3 = vectOfCntrlPts.at(2);
 	cout << p3.x << ',' << p3.y << endl;

 	if(lines.size() >= 1 + controlPoints)	{ color1 = lines.at(1 + controlPoints); }
 	if(lines.size() >= 2 + controlPoints)	{ color2 = lines.at(2 + controlPoints); }
 	if(lines.size() >= 3 + controlPoints)	{ color3 = lines.at(3 + controlPoints); }

 	cout << "Selected colors are: " + color1 + ", "+ color2 + ", "+ color3 << endl;
 	
	vector <Point> Pts1, Pts2, intersectionVect;

	calcPts (p1, p2, numpts, Pts1);
	calcPts (p2, p3, numpts, Pts2);

	ofstream output (filename.c_str());
	
	writeHead (output);
	
	writeLine (output, p1, p2, color1);
	writeLine (output, p2, p3, color1);
	writePts (output, Pts1);
	writePts (output, Pts2);

	//calcLines(output, Pts1, Pts2, color2);

	intersectionVect = calcIntersections(output, Pts1, Pts2, color1);
	intersectionVect.insert(intersectionVect.begin(),Pts1.at(1));
	intersectionVect.push_back(Pts2.at(numpts-1));

	intersectionDotLines(output, intersectionVect , color3);
	intersectionDotLines(output, calcRatio(output, intersectionVect, color1 ), color2 );

	writeTail (output);
	output.close();
	return 0;
}


vector<Point> calcRatio( ostream & outs,const vector<Point> & PV, string color )
{

	vector <Point> ratioPts;
	for (int i = 0; i < PV.size()-1; i++)
	{
		ratioPts.push_back(Point((PV.at(i).x+PV.at(i+1).x)/2, (PV.at(i).y+PV.at(i+1).y)/2));
		//std::printf("Pt: %4.2f %4.2f \n", PV1.at(i).x, PV1.at(i).y);
		//std::printf("Pt: %4.2f %4.2f \n\n", PV2.at(i).x, PV2.at(i).y);
		writeCircle (outs, ratioPts.at(i), 2, color);
		//cout << ratioPts.at(i).x << ','<< ratioPts.at(i).y << endl;
	}
	return ratioPts;
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
	for (int i = 1; i < PV.size(); i++)
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
