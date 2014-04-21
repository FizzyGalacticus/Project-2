//
//  CompoundShapes.h
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#ifndef __CS372Project2__CompoundShapes__
#define __CS372Project2__CompoundShapes__
#include "Shapes.h"
#include <iostream>
#include <vector>
#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::vector;

class CompoundShapes : public Shapes
{
public:
	CompoundShapes();
    virtual ~CompoundShapes();
    virtual string draw() = 0;
    virtual const double & getHeight() const = 0;
    virtual const double & getWidth() const = 0;
protected:
    vector<shared_ptr<Shapes>> _shapes;
    double _height, _width;
};


class Rotated : public CompoundShapes
{
public:
    Rotated(shared_ptr<Shapes> shape, double rotationAngle);
    string draw();
    const double & getHeight() const;
    const double & getWidth() const;
private:
    double _rotationAngle;
    shared_ptr<Shapes> _shape;
    double _width;
    double _height;
};


class Scaled : public CompoundShapes
{
public:
    Scaled(shared_ptr<Shapes> shape, double fx, double fy);
    ~Scaled();
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    double _fx;
    double _fy;
    shared_ptr<Shapes> _shape;
};


class Resize : public CompoundShapes
{
public:
    Resize(shared_ptr<Shapes> shape, double fx, double fy);
    ~Resize();
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    shared_ptr<Shapes> _shape;
};



class Layered : public CompoundShapes
{
public:
    Layered(vector<shared_ptr<Shapes>> shapes);
    string draw();
    const double & getHeight() const;
	const double & getWidth() const;
private:
    vector<shared_ptr<Shapes>> _shapes;
};

class Vertical : public CompoundShapes
{
public:
    Vertical(vector<shared_ptr<Shapes>> shapes);
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    vector<shared_ptr<Shapes>> _shapes;
};

class Horizontal : public CompoundShapes
{
public:
    Horizontal(vector<shared_ptr<Shapes>> shapes);
	string draw();
    const double & getHeight() const;
	const double & getWidth() const;
	
private:
    vector<shared_ptr<Shapes>> _shapes;
};

class Star : public Shapes
{
	public:
		Star(const double width, const double height) : _width(width), _height(height) {}
		const double & getHeight() const {return _height;}
    	const double & getWidth() const {return _width;}
    	string draw()
    	{
    		string drawString = "gsave\n";
    		
    		Triangle myTriangle(300);
    		Rotated upSideDownTriangle(make_shared<Triangle>(myTriangle), 180);
    		
    		string widthFraction =
    			to_string(_width/myTriangle.getWidth());
    		string heightFraction =
    			to_string(_height/(myTriangle.getHeight() + (myTriangle.getHeight()/3)));
    
    		drawString += widthFraction + " " + heightFraction + " scale\n";
    		
    		drawString += upSideDownTriangle.draw();
    		drawString +=
    			"0 " + to_string(myTriangle.getHeight()/3) +
    			" translate\n";
    		drawString += myTriangle.draw();
    		
    		return (drawString + "grestore\n");
    	}
	private:
		double _width, _height;
};

class Boat : public CompoundShapes
{
public:
    Boat(const double width, const double height) : _width(width), _height(height) {}
    const double & getHeight() const {return _height;}
    const double & getWidth() const {return _width;}
    string draw()
    {
        string drawString = "gsave\n";
        
        Triangle myTriangle(300);
        Rotated leftTriangle(make_shared<Triangle>(myTriangle), 90);
        Rotated rightTriangle(make_shared<Triangle>(myTriangle), 270);
        
        Rectangle myRectangle(600, 300);
        
        vector<shared_ptr<Shapes>> bottomOfBoat = {make_shared<Rotated>(leftTriangle), make_shared<Rectangle>(myRectangle), make_shared<Rotated>(rightTriangle)};
        
        Horizontal bottom(bottomOfBoat);
        
        Rectangle flagPoll(20, 400);
        
        Spacer flagSpacer(300, 200);
        
        Rectangle flagRec(300, 200);
        
        Circle myCircle(50);
        
        Star myStar(100, 100);
        
        vector<shared_ptr<Shapes>> myFlagShapes = {make_shared<Rectangle>(flagRec), make_shared<Circle> (myCircle), make_shared<Star>(myStar)};
        
        Layered flag(myFlagShapes);
        
        vector<shared_ptr<Shapes>> flyingFlagShapes = {make_shared<Spacer>(flagSpacer), make_shared<Layered>(flag)};
        
        Vertical flyingFlag(flyingFlagShapes);
        
        vector<shared_ptr<Shapes>> upperBoatShapes = {make_shared<Spacer>(flagSpacer), make_shared<Rectangle>(flagPoll), make_shared<Vertical>(flyingFlag)};
        
        Horizontal upperBoat(upperBoatShapes);
        
        vector<shared_ptr<Shapes>> finalBoatShapes = {make_shared<Horizontal>(bottom), make_shared<Horizontal>(upperBoat)};
        
        Vertical finalBoat(finalBoatShapes);
        
        string widthFraction =
        to_string(_width/finalBoat.getWidth());
        string heightFraction =
        to_string(_height/(finalBoat.getHeight() + (finalBoat.getHeight()/3)));
        
        drawString += widthFraction + " " + heightFraction + " scale\n";
        drawString += finalBoat.draw();
        
        return (drawString + "grestore\n");
    }
private:
    double _width;
    double _height;
};

class Boat2 : public CompoundShapes
{
public:
    Boat2(const double width, const double height) : _width(width), _height(height) {}
    const double & getHeight() const {return _height;}
    const double & getWidth() const {return _width;}
    string draw()
    {
    	double height = 270.0, width = 360.0;
        string scalestring = to_string(_width/width) + " " + to_string(_height/height) + " scale\n",
        	drawString = scalestring + "gsave\n";
        
drawString +=
        string("/inch {72 mul} def\ngsave\n0 0 translate\n10 rotate\nnewpath\n.3 inch .8 inch moveto\n") +
        string("2.52 inch .8 inch lineto\n2.52 inch 1.25 inch lineto\n.3 inch 1.25 inch lineto\n") +
        string("closepath\n0.69 0.39 0.0 setrgbcolor\nfill\ngrestore\nnewpath\n2 inch 1 inch moveto\n") +
        string("3.5 inch 1 inch lineto\n3.5 inch 3.5 inch lineto\n2 inch 3.5 inch lineto\nclosepath\n") +
        string("0.67 .67 .67 setrgbcolor\nfill\nnewpath\n1.8 inch 3.5 inch moveto\n3.7 inch 3.5 inch lineto\n") +
        string("3.7 inch 3.75 inch lineto\n1.8 inch 3.75 inch lineto\nclosepath\n.5 0 0 setrgbcolor\nfill\n") +
        string("newpath\n2.75 inch 2.5 inch .3 inch 0 360 arc\nclosepath\n0 1 1 setrgbcolor\nfill\n") +
        string("gsave\nnewpath\n0 1 inch moveto\n5 inch 2 inch lineto\n4 inch 0 lineto\n.5 inch 0 lineto\n") +
        string("closepath\n0.67 0.33 0.0 setrgbcolor\nfill\ngrestore\n");
      
        return drawString;
    }
private:
    double _width;
    double _height;
};

#endif /* defined(__CS372Project2__CompoundShapes__) */

