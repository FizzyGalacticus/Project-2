//
//  BasicShapes.h
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#ifndef __CS372Project2__BasicShapes__
#define __CS372Project2__BasicShapes__

#include <iostream>
#include <string>
#include <math.h>


using std::string;
using std::to_string;
class BasicShapes
{
public:
    virtual ~BasicShapes() {};
    virtual string draw() = 0;
    virtual double getHeight() = 0;
    virtual double getWidth() = 0;
    
};

class Rectangle : public BasicShapes
{
public:
    Rectangle(double width, double height):_width(width), _height(height){}
    
    double getHeight()
    {
        return _height;
    }
    
    double getWidth()
    {
        return _width;
    }
    
    string draw()
    {
        string height = to_string(_height);
        string width = to_string(_width);
        string leftSide = "0 " + height + " rlineto \n";
        string top = width + " 0 rlineto \n";
        string rightSide = "0 -" + height + " rlineto \n";
        return "newpath\n0 0 moveto\n" + leftSide + top + rightSide + "closepath\nstroke";
    }
private:
    double _height;
    double _width;
    
};
class Polygon : public BasicShapes
{
public:
    virtual ~Polygon() {};
    
    Polygon(double numSides, double sideLength):_numberOfSides(numSides), _sideLength(sideLength)
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
    
    double getHeight()
    {
        return _height;
    }
    
    double getWidth()
    {
        return _width;
    }
    
    string draw()
    {
        string sideLength = to_string(_sideLength);
        string numberOfSides = to_string(_numberOfSides);
        
        double rotationalVariable = 180 - (((_numberOfSides - 2) * 180) /_numberOfSides);
        
        
        double startingPos = (_width - _sideLength)/2;
        string start = "newpath\n";
        string translate = to_string(startingPos) + " 0 translate \n";
        string drawPolygon = "0 1 " + numberOfSides + "{\n0 0 moveto\n" +
            sideLength + " 0 lineto\ncurrentpoint translate\n" +
            to_string(rotationalVariable) + " rotate\n}for \nstroke \n";
        
        return "gsave \n" + start + translate + drawPolygon + "grestore \n";
    }
    
private:
    double _height;
    double _width;
    double _numberOfSides;
    double _sideLength;
};

class Square : public BasicShapes
{
public:
    Square(double sideLength):_sideLength(sideLength) {}
    
    double getHeight()
    {
        return Polygon(4, _sideLength).getHeight();
    }
    
    double getWidth()
    {
        return Polygon(4, _sideLength).getHeight();
    }
    
    string draw()
    {
        return Polygon(4, _sideLength).draw();
    }
    
private:
    double _sideLength;
};

class Triangle : public BasicShapes
{
public:
    Triangle(double sideLength):_sideLength(sideLength) {}
    
    double getHeight()
    {
        return Polygon(3, _sideLength).getHeight();
    }
    
    double getWidth()
    {
        return Polygon(3, _sideLength).getHeight();
    }
    
    string draw()
    {
        return Polygon(3, _sideLength).draw();
    }
private:
    double _sideLength;
};

class Spacer : public BasicShapes
{
public:
    Spacer(double width, double height):_width(width), _height(height){}
    
    double getHeight()
    {
        return _height;
    }
    
    double getWidth()
    {
        return _width;
    }
    
    string draw()
    {
        string height = to_string(_height);
        string width = to_string(_width);
        string leftSide = "0 " + height + " lineto \n";
        string top = width + " " + height + " lineto \n";
        string rightSide =  width + " 0 lineto \n";
        return "newpath " + leftSide + top + rightSide + "closepath \n";
        
    }
private:
    double _height;
    double _width;
    
};
class Circle : public BasicShapes
{
public:
    Circle(double radius):_radius(radius){}
    double getHeight()
    {
        return _radius*2;
    }
    
    double getWidth()
    {
        return _radius*2;
    }
    string draw()
    {
        string radius = to_string(_radius);
        return "newpath " + radius + " " + radius + " " + radius + " 0 360 arc stroke \n";
    }
private:
    double _radius;
};
#endif /* defined(__CS372Project2__BasicShapes__) */
