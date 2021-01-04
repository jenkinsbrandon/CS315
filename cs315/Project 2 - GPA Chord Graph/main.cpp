#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <tuple>
#include "JSONParser.hpp"
#include "Entity.hpp"

std::vector<std::vector<double>> buildMatrix(std::vector<std::tuple<double,double>> intersection );
int findBand( double gpa);
void saveToJSON( std::vector<std::vector<double>> matrix);
int main(int argc, char *argv[]) {

        std::ifstream inputStream;
        inputStream.open(argv[1], std::ios::in);    // open for reading
        if( ! inputStream.is_open()) {
                std::cout << "Unable to open " << argv[1] << ". Terminating..."<<std::endl;
                exit(2);
        }
        inputStream.close();
	JSONTokenizer jsonTokenizer(argv[1]);
	JSONParser jsonParser(jsonTokenizer);
	BinSearchTree *ent1 = new BinSearchTree();
       	jsonParser.parseJSONEntity(ent1);
	//ent1->inorderDump();
	


	JSONTokenizer jsonTokenizer2(argv[2]);
	JSONParser jsonParser2(jsonTokenizer2);
	BinSearchTree *ent2 = new BinSearchTree();
        jsonParser2.parseJSONEntity(ent2);
	//ent2->inorderDump();

	std::vector<std::tuple<double,double>> intersection = ent1->intersection(ent2);	
	//std::cout << intersection.size() << std::endl;
	std::vector<std::vector<double>> matrix = buildMatrix(intersection );
	saveToJSON( matrix);

}

std::vector<std::vector<double>> buildMatrix( std::vector<std::tuple<double,double>> intersection )
{
	std::vector<std::vector<double>> matrix{ { 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0 },
                                                 { 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0 },
                                                 { 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0 },
                                                 { 0, 0, 0, 0, 0, 0, 0, 0 } };

	int i = 0;
	while( i < intersection.size() )
	{
			
		int band1 = findBand( std::get<0>(intersection.at(i)));
		int band2 = findBand( std::get<1>(intersection.at(i)));
		//std::cout << band1 << " " << band2 << std::endl;

		(matrix.at( band2 )).at(band1)++;
	
		i++;
	}
	
	
	return matrix;

}

void saveToJSON( std::vector<std::vector<double>> matrix)
{

	std::ofstream myfile;
	myfile.open("cs315project2.json");

	myfile << "[\n";
	for(int i = 0;  i < matrix.size(); i++ )
	{
		myfile << "\t[";
		for(int j = 0; j < matrix.at(i).size(); j++ )
		{
			if( j < matrix.at(i).size()-1 )
			{
				myfile << matrix[i][j]<< ", ";
	
			}
			else 
			{
				myfile << matrix[i][j]<< "],";
			}

		}
		myfile<<std::endl;	
	}
	myfile << "]"<<std::endl;
	myfile.close();
}

int findBand( double gpa )
{
	if( gpa >= 0.00 && gpa <= 1.67 )
	{
		return 7;
	}
	else if ( gpa > 1.67 && gpa <= 2.0 )
	{
		return 6;
	}
	else if ( gpa > 2.0 && gpa <= 2.3 )
	{
		return 5;
	}

	else if ( gpa > 2.3 && gpa <= 2.67 )
	{
		return 4;
	}

	else if ( gpa > 2.67 && gpa <= 3.0 )
	{
		return 3;
	}

	else if ( gpa > 3.0 && gpa <= 3.3 )
	{
		return 2;
	}

	else if ( gpa > 3.3 && gpa <= 3.67 )
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}	


