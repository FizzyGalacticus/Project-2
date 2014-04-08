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
#include "CompoundShapes.h"
#include <fstream>
using std::ofstream;

int main(int argc, const char * argv[])
{
	ofstream out;
	
    Rectangle myRectangle(40, 50);
    Circle myCircle(50);
    Spacer mySpacer(40, 50);
    
    Polygon myPolygon(36, 50);
    
    Square mySquare(200);
    
    Triangle myTriangle(300);
    
    out.open("/Users/cs/Desktop/Software Construction/Project 2/Project 2/postscript.ps",std::ios::app);
    if(out)
    {
        cout<<"File open"<<endl;
//    	// out << myRectangle.draw() << endl;
//    	// out << "showpage" << endl;
//    	out << Polygon(4,200).draw() << endl;
//    	out << "showpage\n" << endl;
//		out << Polygon(16,100).draw() << endl;
//    	out << "showpage\n" << endl;
//		out << Polygon(8,100).draw() << endl;
//    	out << "showpage\n" << endl;
//        out << Polygon(31, 10).draw() << endl;
//        out << "showpage\n" << endl;
//		out << Polygon(10,100).draw() << endl;
//    	out << "showpage\n" << endl;
//		out << Circle(100).draw() << endl;
//    	out << "showpage\n" << endl;
//    	// out << mySquare.draw() << endl;
//    	// out << "showpage" << endl;
//    	out << myTriangle.draw() << endl;
//    	// out << "showpage" << endl;
        Polygon myPolygon(16, 200);
        out << Scaled<Polygon>(myPolygon, 150 , 70).draw()<<endl;
        out << "showpage" <<endl;
//    	for(auto i = 1; i <= 40; i++)
//        {
//            out << Polygon(i, 20).draw() <<endl;
//            out << "showpage" << endl;
//        }
        out.close();
    }
    else
        cout<<"File not open"<<endl;
    
    return 0;
}

