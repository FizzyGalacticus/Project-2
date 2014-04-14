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

class CompoundShapes : public BasicShapes
{
public:
	CompoundShapes() : _height(0), _width(0) {}
    virtual ~CompoundShapes() {};
    virtual string draw() = 0;
    virtual const double & getHeight() const = 0;
    virtual const double & getWidth() const = 0;
protected:
    vector<shared_ptr<BasicShapes>> _shapes;
    double _height, _width;
};


class Rotated : public CompoundShapes
{
public:
    Rotated(shared_ptr<BasicShapes> shape, double rotationAngle):_shape(shape), _rotationAngle(rotationAngle)
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
    
    string draw()
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
    
    const double & getHeight() const {return _height;}
    const double & getWidth() const {return _width;}
    
private:
    double _rotationAngle;
    shared_ptr<BasicShapes> _shape;
    double _width;
    double _height;
};


class Scaled : public CompoundShapes
{
public:
    Scaled(shared_ptr<BasicShapes> shape, double fx, double fy):_shape(shape), _fx(fx), _fy(fy)
    {
        std::cout<<"Width of the shape: "<<_shape->getWidth()<<std::endl;
        std::cout<<"Height of the shape: "<<_shape->getHeight()<<std::endl;
    	_width = _fx * _shape->getWidth();
        _height = _fy * _shape->getHeight();
    }
    
    ~Scaled(){};
    string draw()
    {
        string fx = to_string(_width);
        string fy = to_string(_height);
        const string comment = "% Scaled shape\n";
        
        return comment + fx + " " + fy + " scale \n" + _shape->draw();
    }
    
	const double & getHeight() const {return _height;}
	const double & getWidth() const {return _width;}
    
private:
    double _fx;
    double _fy;
    shared_ptr<BasicShapes> _shape;
};


class Resize : public CompoundShapes
{
public:
    Resize(shared_ptr<BasicShapes> shape, double fx, double fy):_shape(shape)
    {
        _width = fx;
        _height = fy;
    }
    
    ~Resize(){};
    string draw()
    {
        string widthFraction = to_string(_width/_shape->getWidth());
        string heightFraction = to_string(_height/_shape->getHeight());
        const string comment = "% Scaled shape\n";
        
        return comment + widthFraction + " " + heightFraction + " scale \n" + _shape->draw();
    }
    
	const double & getHeight() const {return _width;}
	const double & getWidth() const {return _height;}
    
private:
    shared_ptr<BasicShapes> _shape;
};



class Layered : public CompoundShapes
{
public:
    Layered(vector<shared_ptr<BasicShapes>> shapes):_shapes(shapes)
    {
    	for(auto i : shapes)
    	{
    		if(i->getHeight() > _height) _height = i->getHeight();
    		if(i->getWidth() > _width) _width = i->getWidth();
    	}
        
        std::cout << "Height of Layered: " << _height << std::endl;
        std::cout << "Width of Layered: " << _width << std::endl;
    }
    
    string draw()
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
    
    const double & getHeight() const {return _height;}
	const double & getWidth() const {return _width;}
    
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};

class Vertical : public CompoundShapes
{
public:
    Vertical(vector<shared_ptr<BasicShapes>> shapes):_shapes(shapes)
    {
    	for(auto i : shapes)
    	{
    		if(i->getWidth() > _width) _width = i->getWidth();
    		_height += i->getHeight();
    	}
    }
    
    string draw()
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
    
	const double & getHeight() const {return _height;}
	const double & getWidth() const {return _width;}
	
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};

class Horizontal : public CompoundShapes
{
public:
    Horizontal(vector<shared_ptr<BasicShapes>> shapes):_shapes(shapes)
    {
    	for(auto i : shapes)
    	{
    		if(i->getHeight() > _height) _height = i->getHeight();
    		_width += i->getWidth();
    	}
    }
    
	string draw()
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
    
    const double & getHeight() const {return _height;}
	const double & getWidth() const {return _width;}
	
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};
#endif /* defined(__CS372Project2__CompoundShapes__) */

