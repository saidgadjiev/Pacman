//
//  CSearchWay.h
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#ifndef CSearchWay_h
#define CSearchWay_h

#include "CStrategyFindWay.h"

class CFindWay {
public:
    CFindWay(CStrategyFindWay *strategy);
    ~CFindWay();
    bool findWay(int *nextY, int *nextX, int i1, int j1, int i2, int j2);
private:
    CStrategyFindWay *_strategy;
};

#endif /* CSearchWay_h */
