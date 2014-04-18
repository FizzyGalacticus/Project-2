//  Dustin Dodson, Igor Kolesnik, Eric Pelto
//  main.cpp
//  Software Construction
//  Project 1

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ofstream;

#include <string>
using std::string;

#include "Shapes.h"
#include "CompoundShapes.h"

const double inches(const double & numberOfInches) {return numberOfInches * 72;}

const int getSideLength()
{
	int input = 3;
	
	cout << "Please enter a desired length for each side: ";
	cin >> input;
	
	return input;
}

const int getNumberOfSides()
{
	int input = 3;
	
	cout << "Please enter a desired number of sides: ";
	cin >> input;
	
	return input;
}

const int getRadius()
{
	int input = 3;
	
	cout << "Please enter a desired radius: ";
	cin >> input;
	
	return input;
}

const Polygon createPolygon()
{
	int numberOfSides = getNumberOfSides();
	int sideLength = inches(getSideLength());
	return Polygon(numberOfSides, sideLength);
}

const Triangle createTriangle()
{
	return Triangle(inches(getSideLength()));
}

const Circle createCircle()
{
	return Circle(inches(getRadius()));
}

const Rectangle createRectangle()
{
	return Rectangle(inches(getSideLength()), inches(getSideLength()));
}

const Square createSquare()
{
	return Square(inches(getSideLength()));
}

void writeShapesToFile(const string & postScript, const string & filename)
{
	ofstream out;
	
	out.open(filename.c_str(), std::ios::out);
	
	if(out)
	{
		out << postScript;
		out.close();
	}
	else cout << "Unable to open \"" << filename << "\" for writing!" << endl;
}

int main(int argc, const char * argv[])
{
	ofstream out;
	const string filename = (argc > 1) ? argv[1] : "postscript.ps";

	

	return 0;
}

