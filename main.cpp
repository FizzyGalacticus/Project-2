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

int main(int argc, const char * argv[])
{
	ofstream out;

	Rectangle myRectangle(40, 50);
	Circle myCircle(50);
	Spacer mySpacer(40, 50);

	Polygon myPolygon(13, 50);

	Square mySquare(200);

	Triangle myTriangle(inches(1));
	
	Rotated myRotated(&myTriangle,180);
	vector<BasicShapes *>  layeredshapes = {&myRotated, &myTriangle},
	myshapes = {&myTriangle, &myRectangle, &myCircle};
	Layered myLayered(layeredshapes);
	Horizontal myHorizontal(myshapes);
	vector<BasicShapes *> stacks = {&myHorizontal, &myHorizontal, &myPolygon};

	out.open("postscript.ps",std::ios::app);
    if(out)
    {
		out << Vertical(stacks).draw();
		out << "showpage" << endl;
		out << "%****************************************%" << endl;
		out << myLayered.draw();
		out << "showpage" << endl;
		out << "%****************************************%" << endl;
    }
	else cout<<"Could not open file"<<endl;

	return 0;
}

