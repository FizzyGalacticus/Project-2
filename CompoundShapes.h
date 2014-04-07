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
private:
    vector<BasicShapes> _shapes;
};

class Rotated : public CompoundShapes
{
    
};

class Scaled : public CompoundShapes
{
    
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
