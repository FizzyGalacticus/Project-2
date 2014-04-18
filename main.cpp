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

const double getSideLength()
{
	double input = 3;
	
	cout << "Please enter a desired length for each side: ";
	cin >> input;
	
	return input;
}

const double getNumberOfSides()
{
	double input = 3;
	
	cout << "Please enter a desired number of sides: ";
	cin >> input;
	
	return input;
}

const double getRadius()
{
	double input = 3;
	
	cout << "Please enter a desired radius: ";
	cin >> input;
	
	return input;
}

const Star createStar()
{
	double height, width;
	
	cout << "Please enter a desired width for the star: ";
	cin >> width;
	cout << "Please enter a desired height for the star: ";
	cin >> height;
	
	return Star(width, height);
}

const Polygon createPolygon()
{
	double numberOfSides = getNumberOfSides();
	double sideLength = inches(getSideLength());
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

shared_ptr<const Shapes> createBasicShape()
{
	int choice = 0;
	
	while(true)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Create a Square" << endl;
		cout << "2. Create a Rectangle" << endl;
		cout << "3. Create a Triangle" << endl;
		cout << "4. Create a Circle" << endl;
		cout << "5. Create a Polygon" << endl;
		cout << "6. Create a Star" << endl;
		cin >> choice;
		
		switch(choice)
		{
			case 1:
				return make_shared<Square>(createSquare());
			break;
			case 2:
				return make_shared<Rectangle>(createRectangle());
			break;
			case 3:
				return make_shared<Triangle>(createTriangle());
			break;
			case 4:
				return make_shared<Circle>(createCircle());
			break;
			case 5:
				return make_shared<Polygon>(createPolygon());
			break;
			case 6:
				return make_shared<Star>(createStar());
			break;
			default:
				cout << "That was not an option." << endl;
		}
	}
}

const string start()
{
	vector<shared_ptr<const Shapes>> createdShapes;
	
	string postScript = "";
	int choice = 0;
	
	while(choice != 8)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Add a Basic Shape to collection" << endl;
		cout << "2. Create a Layered Shape out of collection" << endl;
		cout << "3. Create a Vertical Shape out of collection" << endl;
		cout << "4. Create a Horizontal Shape out of collection" << endl;
		cout << "5. Rotate Current Shapes in collection" << endl;
		cout << "6. Scale current Shapes" << endl;
		cout << "7. Add a New Page (writes current collection)" << endl;
		cout << "8. None, I'm done making shapes!" << endl;
		cin >> choice;
		
		switch(choice)
		{
			case 1:
				
			break;
			case 2:
				
			break;
			case 3:
				
			break;
			case 4:
				
			break;
			case 5:
				
			break;
			case 6:
				
			break;
			case 7:
				
			break;
			case 8:
				
			break;
			default:
				cout << "That was not an option." << endl;
		}
	}
	
	return postScript;
}

int main(int argc, const char * argv[])
{
	ofstream out;
	const string filename = (argc > 1) ? argv[1] : "postscript.ps";

	

	return 0;
}

