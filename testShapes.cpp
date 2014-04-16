//Dustin Dodson, Igor Kolesnik, Eric Pelto
//testShapes.cpp
//TestCases for CPS library

#include <fstream>
using std::ofstream;

#include "Shapes.h"
#include "CompoundShapes.h"

#include <iostream>
using std::cout;
using std::endl;

const double inches(const double & numberOfInches) {return numberOfInches * 72;}

void writeToFile(const string & postScript)
{
	ofstream out;
	
	out.open("testShapes.ps", std::ios::app);
	
	if(out)
	{
		out << postScript << endl;
		out.close();
	}
	else cout << "Couldn't open \"testShapes.ps\" for writing." << endl;
}

void titlePage()
{
	const string centerText = (
		string("/centerText {\ndup\nstringwidth exch\n") +
		string("2 div neg\n4.25 72 mul add\nexch\n") +
		string("2 div neg\n5.5 72 mul add\nmoveto\n} def\n")),
	setFont = "/Times-Roman\nfindfont\n30 scalefont\nsetfont\n",
	printTitle = "(CPS Shape Testing) centerText show\n",
	printAuthors = "(by: Dustin Dodson, Igor Kolesnik, and Eric Pelto) centerText show\n";
	
	writeToFile(centerText + setFont);
	writeToFile(printTitle + "showpage\n");
	writeToFile(printAuthors + "showpage\n");
	writeToFile("%***	BEGIN TESTING	***%\n\n");
}

//Add shapes you wish to test in here!
vector<shared_ptr<Shapes>> createBasicShapes()
{
	vector<shared_ptr<Shapes>> basicShapes;
	basicShapes.push_back(make_shared<Triangle>(inches(3)));
	basicShapes.push_back(make_shared<Square>(inches(3)));
	basicShapes.push_back(make_shared<Rectangle>(inches(3), inches(5)));
	basicShapes.push_back(make_shared<Circle>(inches(1.5)));
	basicShapes.push_back(make_shared<Star>(inches(3.5), inches(3)));
	basicShapes.push_back(make_shared<Vertical>(basicShapes));
	basicShapes.push_back(make_shared<Horizontal>(basicShapes));
	
	return basicShapes;
}

vector< vector< shared_ptr<Shapes > > > createCompoundShapes(const vector<shared_ptr<Shapes>> & basicShapes)
{
	vector< vector< shared_ptr<Shapes > > > allShapes;
	
	for(auto i : basicShapes)
	{
		vector< shared_ptr<Shapes > > temp;
		
		temp.push_back(i);
		temp.push_back(make_shared<Rotated>(i, 90));
		temp.push_back(make_shared<Rotated>(i, 180));
		temp.push_back(make_shared<Rotated>(i, 270));
		temp.push_back(make_shared<Scaled>(i , .5, .5));
		
		allShapes.push_back(temp);
	}
	
	for(auto i : allShapes)
		cout << i.size() << endl;
		
	return allShapes;
}

void ourCoolDrawing()
{
	vector<shared_ptr<Shapes>> colShapes;
	
	Triangle myTriangle(700);
    
    Rotated bottomTriangle(make_shared<Triangle>(myTriangle), 180);
    
    vector<shared_ptr<Shapes>> originalShape = {make_shared<Rotated>(bottomTriangle), make_shared<Triangle>(myTriangle)};
    
    Layered ourShape(originalShape);
    
    for(double i = 600.0; i >= 30.0; i-=2)
    {
        Resize scaledShape(make_shared<Layered>(ourShape), i, i);
        Rotated rotatedShape(make_shared<Resize>(scaledShape), fmod(i,90.0));
        colShapes.push_back(make_shared<Rotated>(rotatedShape));
        
    }
    
    Layered layerCollectionOfFinalShape(colShapes);

    Resize finalResize(make_shared<Layered>(layerCollectionOfFinalShape), inches(8.5), inches(8));
    
    writeToFile(Rotated(make_shared<Resize>(finalResize), 180).draw() + "showpage\n");
}

void testShapes()
{
	vector< vector< shared_ptr<Shapes > > > allShapes = 
		createCompoundShapes(createBasicShapes());
		
	for(auto i : allShapes)
	{
		for(auto j : i)
			writeToFile(j->draw() + "showpage\n");
	}
}

int main()
{
	titlePage();
		
	testShapes();
	
	ourCoolDrawing();
	
	return 0;
}
