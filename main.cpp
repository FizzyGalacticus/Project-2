//  Dustin Dodson, Igor Kolesnik, Eric Pelto
//  main.cpp
//  Software Construction
//  Project 1

#include <iostream>
using std::cout;
using std::endl;
#include "BasicShapes.h"
#include "CompoundShapes.h"
#include <fstream>
using std::ofstream;

const double inches(const double & numberOfInches) {return numberOfInches * 72;}

void writeTests(ofstream & out)
{
	const string nextSection = "showpage\n%****************************************%\n";
	Rectangle myRectangle(40, 50);
	Spacer mySpacer(40, 50);

	Polygon myPolygon(13, 50);

	Square mySquare(inches(2));

	Triangle myTriangle(inches(4));
	
	Circle myCircle(myTriangle.getHeight()/2);
	
	Rotated myRotated(&myTriangle,180);
	vector<BasicShapes *>  layeredshapes = {&myRotated, &myTriangle},
	myshapes = {&myTriangle, &myRectangle, &myCircle};
	Layered myLayered(layeredshapes);
	Horizontal myHorizontal(myshapes);
	vector<BasicShapes *> stacks = {&myHorizontal, &myHorizontal, &myPolygon};
	
	out << myTriangle.draw();
	out << "gsave\n" << (myTriangle.getWidth()/2)-(myCircle.getWidth()/2) << " " << myTriangle.getHeight() << " translate" << endl;
	out << myCircle.draw();
	out << "grestore\n" << endl;
	out << nextSection;
	out << Horizontal(myshapes).draw();
}

int main(int argc, const char * argv[])
{
	ofstream out;

	if(argc > 1)
	{
		out.open(argv[1],std::ios::out);
		if(out)
		{
			writeTests(out);
		}
		else cout<<"Could not open file"<<endl;
	}
	else
	{
		out.open("postscript.ps",std::ios::out);
		if(out)
		{
			writeTests(out);
		}
		else cout<<"Could not open file"<<endl;
	}

	return 0;
}

