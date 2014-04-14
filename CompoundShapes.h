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
	CompoundShapes();
    virtual ~CompoundShapes();
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
    Rotated(shared_ptr<BasicShapes> shape, double rotationAngle);
    string draw();
    const double & getHeight() const;
    const double & getWidth() const;
private:
    double _rotationAngle;
    shared_ptr<BasicShapes> _shape;
    double _width;
    double _height;
};


class Scaled : public CompoundShapes
{
public:
    Scaled(shared_ptr<BasicShapes> shape, double fx, double fy);
    ~Scaled();
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    double _fx;
    double _fy;
    shared_ptr<BasicShapes> _shape;
};


class Resize : public CompoundShapes
{
public:
    Resize(shared_ptr<BasicShapes> shape, double fx, double fy);
    ~Resize();
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    shared_ptr<BasicShapes> _shape;
};



class Layered : public CompoundShapes
{
public:
    Layered(vector<shared_ptr<BasicShapes>> shapes);
    string draw();
    const double & getHeight() const;
	const double & getWidth() const;
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};

class Vertical : public CompoundShapes
{
public:
    Vertical(vector<shared_ptr<BasicShapes>> shapes);
    string draw();
	const double & getHeight() const;
	const double & getWidth() const;
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};

class Horizontal : public CompoundShapes
{
public:
    Horizontal(vector<shared_ptr<BasicShapes>> shapes);
	string draw();
    const double & getHeight() const;
	const double & getWidth() const;
	
private:
    vector<shared_ptr<BasicShapes>> _shapes;
};
#endif /* defined(__CS372Project2__CompoundShapes__) */

