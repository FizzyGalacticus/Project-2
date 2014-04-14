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

vector<shared_ptr<Shapes>> createBasicShapes()
{
	vector<shared_ptr<Shapes>> basicShapes;
	basicShapes.push_back(make_shared<Triangle>(Triangle(inches(3))));
	basicShapes.push_back(make_shared<Square>(Square(inches(3))));
	basicShapes.push_back(make_shared<Rectangle>(Rectangle(inches(3), inches(5))));
	basicShapes.push_back(make_shared<Circle>(Circle(inches(1.5))));
	
	return basicShapes;
}

vector< vector< shared_ptr<Shapes > > > createCompoundShapes(const vector<shared_ptr<Shapes>> & basicShapes)
{
	vector< vector< shared_ptr<Shapes > > > allShapes;
	
	for(auto i : basicShapes)
	{
		vector< shared_ptr<Shapes > > temp;
		
		temp.push_back(i);
		
		allShapes.push_back(temp);
	}
	
	for(auto i : allShapes)
	{
		for(auto j : i)
		{
			Rotated rotatedNinety(j, 90),
				rotatedOneEighty(j, 180), 
				rotatedTwoSeventy(j, 270);
			
			i.push_back(
				make_shared<Rotated>(rotatedNinety));
			i.push_back(
				make_shared<Rotated>(rotatedOneEighty));
			i.push_back(
				make_shared<Rotated>(rotatedTwoSeventy));
			cout << j->draw() << endl;
		}
		cout << i.size() << endl;
	}
	
	return allShapes;
}

void testShapes()
{
	vector< vector< shared_ptr<Shapes > > > allShapes = 
		createCompoundShapes(createBasicShapes());
		
	for(auto i : allShapes)
	{
		for(auto j : i)
		{
			writeToFile(j->draw() + "showpage\n");
		}
	}
}

int main()
{
	titlePage();
		
	testShapes();
	
	return 0;
}
