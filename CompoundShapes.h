//
//  CompoundShapes.h
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#ifndef __CS372Project2__CompoundShapes__
#define __CS372Project2__CompoundShapes__
#include "BasicShapes.h"
#include <iostream>
#include <vector>
using std::vector;

class CompoundShapes
{
public:
    virtual ~CompoundShapes() {};
    virtual string draw() = 0;
private:
    vector<BasicShapes> _shapes;
};

template<typename Shape>
class Rotated : public CompoundShapes
{
public:
    Rotated(Shape shape, double rotationAngle):_shape(shape), _rotationAngle(rotationAngle)
    {}
    
    string draw()
    {
        string rotationAngle = to_string(_rotationAngle);
        
        return rotationAngle + " rotate \n" + _shape.draw;
    }
    
private:
    double _rotationAngle;
    Shape _shape;
};


template<typename Shape>
class Scaled : public CompoundShapes
{
public:
    Scaled(Shape shape, double fx, double fy):_shape(shape), _fx(fx), _fy(fy)
    {}
    
    string draw()
    {
        double width = _fx / _shape.getWidth();
        double height = _fy / _shape.getHeight();
        string fx = to_string(width);
        string fy = to_string(height);
        
        return fx + " " + fy + " scale \n" + _shape.draw();
    }
    
private:
    double _fx;
    double _fy;
    Shape _shape;
};

class Layered : public CompoundShapes
{
     
};

class Vertical : public CompoundShapes
{
    
};

class Horizontal : public CompoundShapes
{
    
};
#endif /* defined(__CS372Project2__CompoundShapes__) */

