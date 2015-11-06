//
//  CSearchWay.cpp
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#include "CFindWay.h"


CFindWay::CFindWay(CStrategyFindWay *strategy):
    _strategy(strategy)
{}

CFindWay::~CFindWay()
{
    delete _strategy;
}

bool CFindWay::findWay(int *nextY, int *nextX, int i1, int j1, int i2, int j2)
{
   return _strategy->findWay(nextY, nextX, i1, j1, i2, j2);
}