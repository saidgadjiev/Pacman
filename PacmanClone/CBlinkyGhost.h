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
#include <queue>
#include <cmath>
#define WEIGHT_CELL 10
class CBlinkyGhost: public CSprite {
public:
    CBlinkyGhost();
    ~CBlinkyGhost();
    void initMap(int **map, int rows, int colls);
    void moveTo(CVector2 position);
private:
    void newMap(int rows, int colls);
    bool findWay(int i1, int j1, int i2, int j2);
    void changeDirection(int i, int j);
    void printWay();
    void newWayXY();
    void deleteWayXY();
    void deleteMap();
    int **_map;
    int _rows;
    int _colls;
    int *_wayX;
    int *_wayY;
    int _lengthWay;
};

#endif /* defined(__PacmanClone__CBlinky__) */
