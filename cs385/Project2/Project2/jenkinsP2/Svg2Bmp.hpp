// File: Svg2Bmp.hpp
// Project: CS 375 Project 2
// Author: Brandon Jenkins
// Description: This file contains the implementations of the functions
//	prototyped in Svg2Bmp.hh

void Svg2Bmp::fillPath (bitmap_image & bmp,  int red, int green, int blue)
{
	//if the fill is not nothing
	if(fill.name != "none")
	{
		//clear the bmp and set to white
		fillBmp.clear();
		fillBmp.set_all_channels(255, 255, 255);

		//For non closed shapes this will close the path from start to finish
		Point start = path.at(0).points.at(0);
		Point end;
		if(path.back().eType == 'Z')
			end = path.at(path.size()-2).points.back();
		else
			end = path.at(path.size()-1).points.back();
		drawPath(fillBmp,path,red,green,blue,1);
		drawLine(fillBmp, start, end, red,green,blue,1);

		//get desired fill points
		vector <Point> fillPoints = getFillPoints();
		vector<Point> colorThese;

		
		//for each fill point, call FILL
		for(int i = 0; i < fillPoints.size(); i++)
		{
			Fill(fillBmp, fillPoints.at(i).x,fillPoints.at(i).y, red, green, blue, colorThese);
		}

		for(int i = 0; i < colorThese.size(); i++)
		{	
			bmp.set_pixel(colorThese.at(i).x,colorThese.at(i).y,red,green,blue);
		}
	}
}

void Svg2Bmp::Fill (bitmap_image & bmp, int currentX, int currentY, int fillRed, int fillGreen, int fillBlue, vector<Point> & colorThese)
{
	rgb_t tempColor;
	bmp.get_pixel(currentX,currentY, tempColor);
	rgb_t color2 = make_colour(255,255,255);
	rgb_t fillColor = make_colour(fillRed, fillGreen, fillBlue);

	//if it is white and not he fill color and within the bounds of the BMP
	if(tempColor == color2 && tempColor != fillColor && currentX < svgWidth && currentX > 1 && currentY > 1 && currentY < svgHeight)
	{
		//set the pixel to the desired fill
		bmp.set_pixel(currentX, currentY, fillColor);
		//add the color in vector
		colorThese.push_back(Point(currentX, currentY));
		//recursively call this function
		Fill(bmp, currentX+1, currentY,fillRed, fillGreen, fillBlue, colorThese);
		Fill(bmp, currentX, currentY+1,fillRed, fillGreen, fillBlue, colorThese);
		Fill(bmp, currentX-1, currentY,fillRed, fillGreen, fillBlue, colorThese);
		Fill(bmp, currentX, currentY-1,fillRed, fillGreen, fillBlue, colorThese);
	}
}

void Svg2Bmp::transformPath ()
{
	for(int j = 0; j < path.size(); j++)
	{
		if(!transformations.empty())
		{
			for(int i = 0; i < transformations.size(); i++)
			{
				switch(transformations.at(i).eType)
				{
					//case rotation
					//this will rotate the points around the x and y with the angle given
					//Uses the same principles as the one from class
					case 'R':
						for(int k = 0; k < path.at(j).points.size(); k++)
						{
							//init a new point to be rotated
							Point newPoint = Point(path.at(j).points.at(k).x, path.at(j).points.at(k).y);
							Point newOriginPoint;

							//set up the new rotational origin if there is one
							if(transformations.at(i).values.size() > 1)
								newOriginPoint = Point(transformations.at(i).values.at(1), transformations.at(i).values.at(2));

							else
								newOriginPoint = Point(0,0);

							debug << "Origin: " << newOriginPoint << endl;
							//get the distance from the origin
							float radius = sqrt( pow( (newPoint.x-newOriginPoint.x),2 ) + pow( (newPoint.y-newOriginPoint.y),2 ) );

							debug << "Radius: " << radius << endl;
							//the original angle the point was at
							float theta = atan2((newPoint.x-newOriginPoint.x), (newPoint.y-newOriginPoint.y));
							debug << "Theta: " << theta<< endl;
							//get the end angle, in radians by adding the new angle 
							theta = theta + ( transformations.at(i).values.at(0)*(M_PI/180)*-1 );
							debug << "Theta: " << theta << endl;

							//set the point to the new angle
							newPoint = Point(radius * sin(theta) + newOriginPoint.x, radius * cos(theta) + newOriginPoint.y);

							debug << path.at(j).points.at(k)<< " -> ";
							path.at(j).points.at(k) = newPoint;
							
							debug << newPoint<< " ";
							debug << endl << endl;
						}
						break;
					//case transform
						//will move the points by the length specified
					case 'T':
						for(int k = 0; k < path.at(j).points.size(); k++)
						{
							debug << path.at(j).points.at(k)<< " ->"; 
							path.at(j).points.at(k) = Point( path.at(j).points.at(k).x + transformations.at(i).values.at(0),
							path.at(j).points.at(k).y + transformations.at(i).values.at(1));
							debug << path.at(j).points.at(k)<<"->";
							debug << transformations.at(i).eType << endl;
						}
						break;
					//case scale
						//will scale by the ration given
					case 'S':
						for(int k = 0; k < path.at(j).points.size(); k++)
						{
							debug << path.at(j).points.at(k)<< "->"; 
							path.at(j).points.at(k) = Point( path.at(j).points.at(k).x * transformations.at(i).values.at(0),
							path.at(j).points.at(k).y * transformations.at(i).values.at(1));
							debug << path.at(j).points.at(k)<<"->";
							debug << transformations.at(i).eType << endl;
						}
						break;
				}
			}
		}
	}
}
