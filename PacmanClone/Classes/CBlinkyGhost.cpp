//
//  CBlinky.cpp
//  PacmanClone
//
//  Created by Саид on 05.09.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CBlinkyGhost.h"

CBlinkyGhost::CBlinkyGhost():
    CSprite(),
    _findWay(nullptr)
{}

CBlinkyGhost::~CBlinkyGhost()
{
    delete _findWay;
}

void CBlinkyGhost::setStrategy(CStrategyFindWay *algorithmfindWay)
{
    _findWay = new CFindWay(algorithmfindWay);
}

void CBlinkyGhost::moveTo(CVector2 targetPosition)
{
    CVector2 position = targetPosition;
    int j2 = position.x / SQUARE_SIZE;
    int i2 = position.y / SQUARE_SIZE;
    int j1 = _position.x / SQUARE_SIZE;
    int i1 = _position.y / SQUARE_SIZE;
    
    _findWay->findWay(&_nextY, &_nextX, i1, j1, i2, j2);
    changeDirection(_nextY, _nextX);
    move();
}

void CBlinkyGhost::changeDirection(int i, int j)
{
    CVector2 position;
    getCenterPositionSideSquare(&position);
    int y = position.y / SQUARE_SIZE;
    int x = position.x / SQUARE_SIZE;
    
    if (y == i && x < j) {
        _direction = RIGHT;
    }
    if (y == i && x > j) {
        _direction = LEFT;
    }
    if (x == j && y < i) {
        _direction = DOWN;
    }
    if (x == j && y > i) {
        _direction = UP;
    }
}

