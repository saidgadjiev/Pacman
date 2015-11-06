//
//  CStrategy.h
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#ifndef CStrategy_h
#define CStrategy_h

#include "CLevel.h"

class CStrategyFindWay {
public:
    virtual ~CStrategyFindWay() {};
    virtual bool findWay(int *nextY, int *nextX, int i1, int j1, int i2, int j2) = 0;
    virtual void initMap(int **map, int rows, int colls) = 0;
};

#endif /* CStrategy_h */
