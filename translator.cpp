//  Dustin Dodson, Igor Kolesnik, Eric Pelto
//  translator.cpp
//  Software Construction
//  Project 1

#include <stdlib.h>

//***********IF ON WINDOWS**************
	#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__)

	inline void clearScreen() {system("cls");}

//**********IF ON LINUX*****************
#elif defined(__linux__) || defined(linux) || defined(__linux)

	inline void clearScreen() {system("clear");}

//***********IF ON MAC******************
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)

	inline void clearScreen() {system("clear");}

#endif

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ofstream;

#include <string>
using std::string;

#include <utility>

#include "Shapes.h"
#include "CompoundShapes.h"

const double inches(const double & numberOfInches) {return numberOfInches * 72;}

const std::pair<double,double> getWidthAndHeight()
{
	double width, height;
	cout << "Please enter a desired width: ";
	cin >> width;
	cout << "Please enter a desired height: ";
	cin >> height;
	clearScreen();
	
	return std::pair<double,double>(width,height);
}

const double getSideLength()
{
	double input = 3;
	
	cout << "Please enter a desired length for each side: ";
	cin >> input;
	clearScreen();
	
	return input;
}

const double getNumberOfSides()
{
	double input = 3;
	
	cout << "Please enter a desired number of sides: ";
	cin >> input;
	clearScreen();
	
	return input;
}

const double getRadius()
{
	double input = 3;
	
	cout << "Please enter a desired radius: ";
	cin >> input;
	clearScreen();
	
	return input;
}

vector<shared_ptr<Shapes>> getRotated(const vector<shared_ptr<Shapes>> originalShapes)
{
	vector<shared_ptr<Shapes>> newShapes;
	int input = 0;
	double rotationAngle = 0;
	
	while(input != 1 && input != 2 && input != 3)
	{
		cout << "How much would you like to rotate your shapes?" << endl;
		cout << "1. 90 degrees." << endl;
		cout << "2. 180 degrees." << endl;
		cout << "3. 270 degrees." << endl;
		cin >> input;
		clearScreen();
		
		switch(input)
		{
			case 1:
				rotationAngle = 90.0;
			break;
			case 2:
				rotationAngle = 180.0;
			break;
			case 3:
				rotationAngle = 270.0;
			break;
		}
	}
	
	for(auto shape : originalShapes)
		newShapes.push_back(make_shared<Rotated>(shape, rotationAngle));
	
	return newShapes;
}

vector<shared_ptr<Shapes>> getScaled(const vector<shared_ptr<Shapes>> originalShapes)
{
	vector<shared_ptr<Shapes>> newShapes;
	double input = 1;
	double rotationAngle = 0;
	
	cout << "Please enter desired scaling factor: ";
	cin >> input;
	clearScreen();
	
	if(input < 0) input = (0-input);
	
	for(auto shape : originalShapes)
		newShapes.push_back(make_shared<Scaled>(shape, input, input));
	
	return newShapes;
}

Star createStar()
{
	double height, width;
	
	const std::pair<double,double> widthAndHeight = getWidthAndHeight();
	
	return Star(inches(widthAndHeight.first), inches(widthAndHeight.second));
}

Polygon createPolygon()
{
	double numberOfSides = getNumberOfSides();
	double sideLength = inches(getSideLength());
	return Polygon(numberOfSides, sideLength);
}

Triangle createTriangle()
{
	return Triangle(inches(getSideLength()));
}

Circle createCircle()
{
	return Circle(inches(getRadius()));
}

Rectangle createRectangle()
{
	std::pair<double,double> widthAndHeight = getWidthAndHeight();
	
	return Rectangle(inches(widthAndHeight.first), inches(widthAndHeight.second));
}

Square createSquare()
{
	return Square(inches(getSideLength()));
}

void writeShapesToPostScriptString(vector<shared_ptr<Shapes>> & createdShapes, string & postScript)
{
	if(createdShapes.size())
	{
		double totalWidth = 0;
		postScript += "gsave\n";
		for(auto shape : createdShapes)
		{
			postScript += shape->draw();
			totalWidth += shape->getWidth();
			postScript += to_string(totalWidth) + " 0 moveto\n";
		}
		postScript += "grestore\nshowpage\n";
		createdShapes.clear();
	}
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

shared_ptr<Shapes> createBasicShape()
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
		clearScreen();
		
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
	vector<shared_ptr<Shapes>> createdShapes, temp;
	
	string postScript = "";
	int choice = 0;
	
	while(true)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Add a Basic Shape to collection" << endl;
		cout << "2. Create a Layered Shape out of collection" << endl;
		cout << "3. Create a Vertical Shape out of collection" << endl;
		cout << "4. Create a Horizontal Shape out of collection" << endl;
		cout << "5. Rotate Current Shapes in collection" << endl;
		cout << "6. Scale current Shapes" << endl;
		cout << "7. Write current collection to page" << endl;
		cout << "8. None, I'm done making shapes!" << endl;
		cin >> choice;
		clearScreen();
		
		switch(choice)
		{
			case 1:
				createdShapes.push_back(createBasicShape());
			break;
			case 2:
				temp.push_back(make_shared<Layered>(createdShapes));
				createdShapes = temp;
				temp.clear();
			break;
			case 3:
				temp.push_back(make_shared<Vertical>(createdShapes));
				createdShapes = temp;
				temp.clear();
			break;
			case 4:
				temp.push_back(make_shared<Horizontal>(createdShapes));
				createdShapes = temp;
				temp.clear();
			break;
			case 5:
				createdShapes = getRotated(createdShapes);
			break;
			case 6:
				createdShapes = getScaled(createdShapes);
			break;
			case 7:
				writeShapesToPostScriptString(createdShapes, postScript);
			break;
			case 8:
				writeShapesToPostScriptString(createdShapes, postScript);
				return postScript;
			break;
			default:
				cout << "That was not an option." << endl;
		}
	}
}

int main(int argc, const char * argv[])
{
	ofstream out;
	const string filename = (argc > 1) ? argv[1] : "postscript.ps";

	clearScreen();
	writeShapesToFile(start(), filename);

	return 0;
}

