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
//	const string nextSection = "showpage\n%****************************************%\n";
//	Rectangle myRectangle(40, 50);
//	Spacer mySpacer(40, 50);
//
//	Polygon myPolygon(13, 50);
//
//	Square mySquare(inches(2));
//
//	Triangle myTriangle(inches(4));
//	
//	Circle myCircle(myTriangle.getHeight()/2);
//	
//	Rotated myRotated(make_shared<Triangle>(myTriangle),180);
//	vector<shared_ptr<BasicShapes>>  layeredshapes = {make_shared<Rotated>(myRotated), make_shared<Triangle>(myTriangle)},
//        myshapes = {make_shared<Triangle>(myTriangle), make_shared<Rectangle>(myRectangle), make_shared<Circle>(myCircle)};
//	Layered myLayered(layeredshapes);
//	Horizontal myHorizontal(myshapes);
//	vector<BasicShapes *> stacks = {&myHorizontal, &myHorizontal, &myPolygon};
//	
//	out << myTriangle.draw();
//	out << "gsave\n" << (myTriangle.getWidth()/2)-(myCircle.getWidth()/2) << " " << myTriangle.getHeight() << " translate" << endl;
//	out << myCircle.draw();
//	out << "grestore\n" << endl;
//	out << nextSection;
//	out << Horizontal(myshapes).draw();
    
    vector<shared_ptr<BasicShapes>> myShapes;
    
    for(auto i = 100; i >= 3; i-=2)
    {
        Polygon myPolygon(i, inches(3));
        Rotated myRotated(make_shared<Polygon>(myPolygon), 90);
        myShapes.push_back(make_shared<Rotated>(myRotated));
    }
    
    Polygon myPolygon(20, inches(3));
    
    Layered myLayeredShapes(myShapes);
    
    Scaled scaledShapes(make_shared<Layered>(myLayeredShapes), inches(8.5), inches(11));
    
    out << scaledShapes.draw();
    out << "showpage"<<endl;
    
//    vector<shared_ptr<BasicShapes>> colShapes;
    
    
    
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

