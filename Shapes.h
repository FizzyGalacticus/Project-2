//
//  Shapes.h
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#ifndef __CS372Project2__Shapes__
#define __CS372Project2__Shapes__

#include <iostream>
#include <string>
#include <math.h>
using std::string;
using std::to_string;

class Shapes
{
public:
    virtual ~Shapes();
    virtual string draw() = 0;
    virtual const double & getHeight() const = 0;
    virtual const double & getWidth() const = 0;
    
};

class Rectangle : public Shapes
{
public:
    Rectangle(double width, double height);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
private:
    double _height;
    double _width;
    
};
class Polygon : public Shapes
{
public:
    virtual ~Polygon();
    Polygon(double numSides, double sideLength);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
private:
    double _height;
    double _width;
    double _numberOfSides;
    double _sideLength;
};

class Square : public Shapes
{
public:
    Square(double sideLength);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
    
private:
    double _sideLength;
};

class Triangle : public Shapes
{
public:
    Triangle(double sideLength);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
private:
    double _sideLength;
};

class Spacer : public Shapes
{
public:
    Spacer(double width, double height);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
private:
    double _height;
    double _width;
    
};
class Circle : public Shapes
{
public:
    Circle(double radius);
    const double & getHeight() const;
    const double & getWidth() const;
    string draw();
private:
    double _radius;
    double _diameter;
};
#endif /* defined(__CS372Project2__Shapes__) */
