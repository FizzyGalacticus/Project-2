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
#endif /* defined(__CS372Project2__CompoundShapes__) */

