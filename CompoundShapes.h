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
#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::vector;

class CompoundShapes
{
public:
    virtual ~CompoundShapes() {};
    virtual string draw() = 0;
protected:
    vector<BasicShapes *> _shapes;
};


class Rotated : public CompoundShapes
{
public:
    Rotated(BasicShapes* shape, double rotationAngle):_shape(shape), _rotationAngle(rotationAngle)
    {
        if(_rotationAngle == 90 || _rotationAngle == 270)
        {
            _width = _shape->getHeight();
            _height = _shape->getWidth();
        }
        else if (_rotationAngle == 180)
        {
            _width = _shape->getWidth();
            _height = _shape->getHeight();
        }
    
    
    }
    
    string draw()
    {
        if(_rotationAngle == 90)
        {
            return string("gsave\n"+to_string(_width)+" 0 translate "+to_string(_rotationAngle)+" rotate\n"+_shape->draw()+"grestore\n");
        }
        if(_rotationAngle == 270)
        {
            return string("gsave\n0 "+to_string(_height)+" translate "+to_string(_rotationAngle)+" rotate\n"+_shape->draw()+"grestore\n");
        }

        return "gsave \n" + to_string(_width) + " " + to_string(_height) + " translate \n" + to_string(_rotationAngle) +" rotate \n" + _shape->draw() + "grestore\n";
    }
    
private:
    double _rotationAngle;
    BasicShapes* _shape;
    double _width;
    double _height;
};


class Scaled : public CompoundShapes
{
public:
    Scaled(BasicShapes* shape, double fx, double fy):_shape(shape), _fx(fx), _fy(fy)
    {}
    
    ~Scaled(){};
    string draw()
    {
        double width = _fx / _shape->getWidth();
        double height = _fy / _shape->getHeight();
        string fx = to_string(width);
        string fy = to_string(height);
        
        return fx + " " + fy + " scale \n" + _shape->draw();
    }
    
private:
    double _fx;
    double _fy;
    BasicShapes* _shape;
};


class Layered : public CompoundShapes
{
public:
    Layered(vector<BasicShapes*> shapes):_shapes(shapes){}
    
    string draw()
    {
        string translatePos;
        string drawShapes;
        double widthOfLargestShape = 0;
        double heightOfLargestShape = 0;
        double middleWidthOfLargestShape = 0;
        double middleHeightOfLargestShape = 0;
        
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
            translatePos = "gsave \n" + to_string(posX) + " " + to_string(posY) + " translate \n" +
            i->draw() + "grestore \n";
            
            drawShapes += translatePos;
        }
        
        return drawShapes;

    }
private:
    vector<BasicShapes *> _shapes;
};

class Vertical : public CompoundShapes
{
public:
    Vertical(vector<BasicShapes*> shapes):_shapes(shapes){}
    
    string draw()
    {
        string translatePos;
        string drawShapes;
        double widthOfLargestShape = 0;
        double heightOfLargestShape = 0;
        double middleWidthOfLargestShape = 0;
        double middleHeightOfLargestShape = 0;
        
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
        
        double previousHeight = 0;
        
        for(auto i : _shapes)
        {
            double middleWidthOfShape = i->getWidth()/2;
            double posX = middleWidthOfLargestShape - middleWidthOfShape;
            translatePos = "gsave \n" + to_string(posX) + " " + to_string(previousHeight) + " translate \n" +
            i->draw() + "grestore \n";
            
            drawShapes += translatePos;
            previousHeight += i->getHeight();
        }
        
        return drawShapes;
        
    }
private:
    vector<BasicShapes *> _shapes;
};

class Horizontal : public CompoundShapes
{
public:
    Horizontal(vector<BasicShapes*> shapes):_shapes(shapes){}
    
    string draw()
    {
        string translatePos;
        string drawShapes;
        double widthOfLargestShape = 0;
        double heightOfLargestShape = 0;
        double middleWidthOfLargestShape = 0;
        double middleHeightOfLargestShape = 0;
        
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
        
        double previousWidth = 0;
        
        for(auto i : _shapes)
        {
            double middleHeightOfShape = i->getHeight()/2;
            double posY = middleHeightOfLargestShape - middleHeightOfShape;
            translatePos = "gsave \n" + to_string(previousWidth) + " " + to_string(posY) + " translate \n" +
            i->draw() + "grestore \n";
            
            drawShapes += translatePos;
            previousWidth += i->getWidth();
        }
        
        return drawShapes;
        
    }
private:
    vector<BasicShapes *> _shapes;
};
#endif /* defined(__CS372Project2__CompoundShapes__) */

