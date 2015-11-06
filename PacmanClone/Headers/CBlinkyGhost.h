//
//  CBlinky.h
//  PacmanClone
//
//  Created by Саид on 05.09.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CBlinky__
#define __PacmanClone__CBlinky__
#include "CSprite.h"
#include "CLevel.h"
#include "CFindWay.h"
#include "CWaveAlgorithm.h"
#include <queue>
#include <cmath>
#define WEIGHT_CELL 10

class CBlinkyGhost: public CSprite {
public:
    CBlinkyGhost();
    ~CBlinkyGhost();
    void setStrategy(CStrategyFindWay *algorithmFindWay);
    void moveTo(CVector2 position);
private:
    CFindWay *_findWay;
    void changeDirection(int i, int j);
    int _nextX;
    int _nextY;
};

#endif /* defined(__PacmanClone__CBlinky__) */
