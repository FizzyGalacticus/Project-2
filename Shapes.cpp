//
//  Shapes.cpp
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#include "Shapes.h"

Shapes::~Shapes(){};

Rectangle::Rectangle(double width, double height):_width(width), _height(height){}

const double & Rectangle::getHeight() const
{
    return _height;
}

const double & Rectangle::getWidth() const
{
    return _width;
}

string Rectangle::draw()
{
    string height = to_string(_height);
    string width = to_string(_width);
    string leftSide = "0 " + height + " rlineto \n";
    string top = width + " 0 rlineto \n";
    string rightSide = "0 -" + height + " rlineto \n";
    return "newpath\n0 0 moveto\n" + leftSide + top + rightSide + "closepath\nstroke\n";
}

Polygon::~Polygon(){};

Polygon::Polygon(double numSides, double sideLength):_numberOfSides(numSides), _sideLength(sideLength)
{
    if(fmod(_numberOfSides, 2) == 1)
    {
        _height = _sideLength*(1+cos(M_PI/_numberOfSides))/(2*sin(M_PI/_numberOfSides));
        _width = (_sideLength * sin(M_PI*(_numberOfSides-1)/(2*_numberOfSides)))/(sin(M_PI/_numberOfSides));
    }
    else if(fmod(_numberOfSides, 4) == 0)
    {
        _height = _sideLength*(cos(M_PI/_numberOfSides))/(sin(M_PI/_numberOfSides));
        _width = (_sideLength*cos(M_PI/_numberOfSides))/(sin(M_PI/_numberOfSides));
    }
    else
    {
        _height = _sideLength*(cos(M_PI/_numberOfSides))/(sin(M_PI/_numberOfSides));
        _width = _sideLength/(sin(M_PI/_numberOfSides));
    }
}

const double & Polygon::getHeight() const
{
    return _height;
}

const double & Polygon::getWidth() const
{
    return _width;
}

string Polygon::draw()
{
    string sideLength = to_string(_sideLength);
    string numberOfSides = to_string(int(_numberOfSides));
    
    double rotationalVariable = 180 - (((_numberOfSides - 2) * 180) /_numberOfSides);
    
    
    double startingPos = (_width - _sideLength)/2;
    string start = "newpath\n";
    string translate = to_string(int(startingPos)) + " 0 translate \n";
    string drawPolygon = "0 1 " + numberOfSides + "{\n0 0 moveto\n" +
    sideLength + " 0 lineto\ncurrentpoint translate\n" +
    to_string(rotationalVariable) + " rotate\n}for \nstroke \n";
    
    return "gsave \n" + start + translate + drawPolygon + "grestore \n\n";
}

Square::Square(double sideLength):_sideLength(sideLength) {}

const double & Square::getHeight() const
{
    return Polygon(4, _sideLength).getHeight();
}

const double & Square::getWidth() const
{
    return Polygon(4, _sideLength).getHeight();
}

string Square::draw()
{
    return Polygon(4, _sideLength).draw();
}

Triangle::Triangle(double sideLength):_sideLength(sideLength) {}

const double & Triangle::getHeight() const
{
    return Polygon(3, _sideLength).getHeight();
}

const double & Triangle::getWidth() const
{
    return Polygon(3, _sideLength).getWidth();
}

string Triangle::draw()
{
    return Polygon(3, _sideLength).draw();
}

Spacer::Spacer(double width, double height):_width(width), _height(height){}

const double & Spacer::getHeight() const
{
    return _height;
}

const double & Spacer::getWidth() const
{
    return _width;
}

string Spacer::draw()
{
    string height = to_string(_height);
    string width = to_string(_width);
    string leftSide = "0 " + height + " lineto \n";
    string top = width + " " + height + " lineto \n";
    string rightSide =  width + " 0 lineto \n";
    return "newpath " + leftSide + top + rightSide + "closepath \n";
    
}

Circle::Circle(double radius):_radius(radius), _diameter(radius*2) {}
const double & Circle::getHeight() const
{
    return _diameter;
}

const double & Circle::getWidth() const
{
    return _diameter;
}
string Circle::draw()
{
    string radius = to_string(_radius);
    return "newpath " + radius + " " + radius + " " + radius + " 0 360 arc stroke \n";
}




















