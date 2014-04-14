//
//  CompoundShapes.cpp
//  CS372Project2
//
//  Created by CS on 4/6/14.
//  Copyright (c) 2014 Computer Science. All rights reserved.
//

#include "CompoundShapes.h"

CompoundShapes::CompoundShapes() : _height(0), _width(0) {}

CompoundShapes::~CompoundShapes() {};

Rotated::Rotated(shared_ptr<Shapes> shape, double rotationAngle):_shape(shape), _rotationAngle(rotationAngle)
{
    if(_rotationAngle == 90 || _rotationAngle == 270)
    {
        _width = _shape->getHeight();
        _height = _shape->getWidth();
    }
    else
    {
        _width = _shape->getWidth();
        _height = _shape->getHeight();
    }
    
    
}

string Rotated::draw()
{
    const string comment = "% Rotated shape\n";
    if(_rotationAngle == 90)
    {
        return comment + string("gsave\n"+to_string(_width)+" 0 translate "+to_string(int(_rotationAngle))+" rotate\n"+_shape->draw()+"grestore\n\n");
    }
    if(_rotationAngle == 270)
    {
        return comment + string("gsave\n0 "+to_string(_height)+" translate "+to_string(int(_rotationAngle))+" rotate\n"+_shape->draw()+"grestore\n\n");
    }
    
    return comment + "gsave \n" + to_string(_width) + " " + to_string(_height) + " translate \n" + to_string(int(_rotationAngle)) +" rotate \n" + _shape->draw() + "grestore\n\n";
}

const double & Rotated::getHeight() const {return _height;}
const double & Rotated::getWidth() const {return _width;}

Scaled::Scaled(shared_ptr<Shapes> shape, double fx, double fy):_shape(shape), _fx(fx), _fy(fy)
{
    _width = _fx * _shape->getWidth();
    _height = _fy * _shape->getHeight();
}

Scaled::~Scaled(){};
string Scaled::draw()
{
    string fx = to_string(_width);
    string fy = to_string(_height);
    const string comment = "% Scaled shape\n";
    
    return comment + fx + " " + fy + " scale \n" + _shape->draw();
}

const double & Scaled::getHeight() const {return _height;}
const double & Scaled::getWidth() const {return _width;}

Resize::Resize(shared_ptr<Shapes> shape, double fx, double fy):_shape(shape)
{
    _width = fx;
    _height = fy;
}

Resize::~Resize(){};
string Resize::draw()
{
    string widthFraction = to_string(_width/_shape->getWidth());
    string heightFraction = to_string(_height/_shape->getHeight());
    const string comment = "% Scaled shape\n";
    
    return comment + widthFraction + " " + heightFraction + " scale \n" + _shape->draw();
}

const double & Resize::getHeight() const {return _width;}
const double & Resize::getWidth() const {return _height;}

Layered::Layered(vector<shared_ptr<Shapes>> shapes):_shapes(shapes)
{
    for(auto i : shapes)
    {
        if(i->getHeight() > _height) _height = i->getHeight();
        if(i->getWidth() > _width) _width = i->getWidth();
    }
}

string Layered::draw()
{
    string translatePos;
    string drawShapes;
    double widthOfLargestShape = 0;
    double heightOfLargestShape = 0;
    double middleWidthOfLargestShape = 0;
    double middleHeightOfLargestShape = 0;
    const string comment = "% Layered shapes\n";
    
    for(auto i : _shapes)
    {
        if(i->getWidth() > widthOfLargestShape)
        {
            widthOfLargestShape = i->getWidth();
            middleWidthOfLargestShape = i->getWidth()/2;
            
        }
        if(i->getHeight() > heightOfLargestShape)
        {
            heightOfLargestShape = i->getWidth();
            middleHeightOfLargestShape = i->getWidth()/2;
        }
        
    }
    
    
    for(auto i : _shapes)
    {
        double middleWidthOfShape = i->getWidth()/2;
        double middleHeightOfShape = i->getHeight()/2;
        double posX = middleWidthOfLargestShape - middleWidthOfShape;
        double posY = middleHeightOfLargestShape - middleHeightOfShape;
        translatePos = "gsave \n" + to_string(int(posX)) + " " + to_string(int(posY)) + " translate \n" +
        i->draw() + "grestore \n\n";
        
        drawShapes += translatePos;
    }
    
    return comment + drawShapes;
    
}

const double & Layered::getHeight() const {return _height;}
const double & Layered::getWidth() const {return _width;}

Vertical::Vertical(vector<shared_ptr<Shapes>> shapes):_shapes(shapes)
{
    for(auto i : shapes)
    {
        if(i->getWidth() > _width) _width = i->getWidth();
        _height += i->getHeight();
    }
}

string Vertical::draw()
{
    string drawString;
    double currentHeight = 0;
    for(auto i : _shapes)
    {
        drawString += ("gsave\n" + to_string(int((_width/2)-(i->getWidth()/2))) +
                       " " + to_string(int(currentHeight)) + " translate\n");
        drawString += i->draw();
        drawString += "grestore\n\n";
        
        currentHeight += i->getHeight();
    }
    
    return drawString;
}

const double & Vertical::getHeight() const {return _height;}
const double & Vertical::getWidth() const {return _width;}

Horizontal::Horizontal(vector<shared_ptr<Shapes>> shapes):_shapes(shapes)
{
    for(auto i : shapes)
    {
        if(i->getHeight() > _height) _height = i->getHeight();
        _width += i->getWidth();
    }
}

string Horizontal::draw()
{
    string drawString;
    double currentWidth = 0;
    for(auto i : _shapes)
    {
        drawString += ("gsave\n" + to_string(int(currentWidth)) +
                       " " + to_string(int((_height/2)-(i->getHeight()/2))) +
                       " translate\n");
        drawString += i->draw();
        drawString += "grestore\n\n";
        
        currentWidth += i->getWidth();
    }
    
    return drawString;
}

const double & Horizontal::getHeight() const {return _height;}
const double & Horizontal::getWidth() const {return _width;}


















