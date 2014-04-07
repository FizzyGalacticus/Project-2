//  Dustin Dodson, Igor Kolesnik, Eric Pelto
//  main.cpp
//  Software Construction
//  Project 1
//
//

#include <iostream>
using std::cout;
using std::endl;
#include "BasicShapes.h"
#include <fstream>
using std::ofstream;

int main(int argc, const char * argv[])
{
	ofstream out;
	
    Rectangle myRectangle(40, 50);
    Circle myCircle(50);
    Spacer mySpacer(40, 50);
    
    Polygon myPolygon(8, 100);
    
    Square mySquare(200);
    
    Triangle myTriangle(300);
    
    out.open("postscript.ps",std::ios::app);
    if(out)
    {
    	out << myRectangle.draw() << endl;
    	out << "showpage" << endl;
    	out << myPolygon.draw() << endl;
    	out << "showpage" << endl;
    	out << mySquare.draw() << endl;
    	out << "showpage" << endl;
    	out << myTriangle.draw() << endl;
    	out << "showpage" << endl;
    	out.close();
    }
    
    return 0;
}

