//
//  CBlinky.cpp
//  PacmanClone
//
//  Created by Саид on 05.09.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CBlinkyGhost.h"


struct Node {
    int _x;
    int _y;
    int _G;
    int _F;
    
    Node(int x, int y, int G, int F);
    void updateF(int x, int y);
    int estimate(int x, int y);
    void nextLevel();
};

Node::Node(int x, int y, int G, int F):
_x(x),
_y(y),
_G(G),
_F(F)
{}

void Node::updateF(int x, int y)
{
    _F = estimate(x, y) * WEIGHT_CELL + _G;
}

int Node::estimate(int x, int y)
{
    return sqrt((x - _x) * (x - _x)) + sqrt((y- _y) * (y - _y));
}

void Node::nextLevel()
{
    _G += WEIGHT_CELL;
}

bool operator < (const Node &_x, const Node &_y)
{
    return _x._F < _y._F;
}

CBlinkyGhost::CBlinkyGhost():
    CSprite(),
    _map(nullptr),
    _wayX(nullptr),
    _wayY(nullptr),
    _lengthWay(0)
{}

CBlinkyGhost::~CBlinkyGhost()
{
    deleteWayXY();
    deleteMap();
}

void CBlinkyGhost::deleteWayXY()
{
    delete _wayX;
    delete _wayY;
    _wayX = nullptr;
    _wayY = nullptr;
    _lengthWay = 0;
}

void CBlinkyGhost::deleteMap()
{
    for (int i = 0; i < _rows; i++) {
        delete [] _map[i];
    }
    _map = nullptr;
    _wayX = nullptr;
    _wayY = nullptr;
}

void CBlinkyGhost::initMap(int **maze, int rows, int colls)
{
    newMap(rows, colls);
    newWayXY();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colls; j++) {
            if (maze[i][j] == 0) {
                _map[i][j] = -1;
            } else {
                _map[i][j] = -2;
            }
        }
    }
}

void CBlinkyGhost::newMap(int rows, int colls)
{
    _rows = rows;
    _colls = colls;
    _map = new int*[_rows];
    
    for (int i = 0; i < _rows; i++) {
        _map[i] = new int[_colls];
    }
}

void CBlinkyGhost::moveTo(CVector2 targetPosition)
{
    CVector2 position = targetPosition;
    int j2 = position.x / SQUARE_SIZE;
    int i2 = position.y / SQUARE_SIZE;
    int j1 = _position.x / SQUARE_SIZE;
    int i1 = _position.y / SQUARE_SIZE;
    
    findWay(i1, j1, i2, j2);
    changeDirection(_wayY[_lengthWay - 1], _wayX[_lengthWay - 1]);
    /*std::cout << _wayY[_lengthWay - 1] << " " << _wayX[_lengthWay - 1] << std::endl;*/
    move();
    printWay();
    //exit(EXIT_FAILURE);
}

void CBlinkyGhost::newWayXY()
{
    _wayX = new int[_rows * _colls];
    _wayY = new int[_rows * _colls];
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

bool CBlinkyGhost::findWay(int i1, int j1, int i2, int j2)
{
    /*
    int WALL = -1;
    int WAY = -2;
    int tmp[_rows][_colls];
    bool stop = true;
    int di[4] = {1, 0, -1, 0};
    int dj[4] = {0, 1, 0, -1};
    
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _colls; j++) {
            tmp[i][j] = _map[i][j];
        }
    }
    
    if (tmp[i1][j1] == WALL || tmp[i2][j2] == WALL) {
        return false;
    }
    int d = 0;
    tmp[i1][j1] = 0;
    do {
        stop = true;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _colls; j++) {
                if (tmp[i][j] == d) {
                    for (int k = 0; k < 4; k++) {
                        int ix = i + di[k], jy = j + dj[k];
                        if (ix < _rows && ix >= 0 && jy < _colls && jy >= 0 && tmp[ix][jy] == WAY) {
                            stop = false;
                            tmp[ix][jy] = d + 1;
                        }
                    }
                }
            }
        }
        d++;
    } while (!stop && tmp[i2][j2] == WAY);
    if (tmp[i2][j2] == WAY) {
        return false;
    }
    _lengthWay = tmp[i2][j2];
    int i = i2;
    int j = j2;
    d = _lengthWay;
    
    while (d > 0) {
        _wayY[d] = i;
        _wayX[d] = j;
        d--;
        for (int k = 0; k < 4; k++) {
            int ix = i + di[k], jy = j + dj[k];
            if (ix < _rows && ix >= 0 && jy < _colls && jy >= 0 && tmp[ix][jy] == d) {
                i = ix;
                j = jy;
                break;
            }
        }
    }
    _wayY[0] = i1;
    _wayX[0] = j1;
    
    return true;
  */
    _lengthWay = 0;
    int WALL = -1;
    int WAY = -2;
    int countDir = 4;
    int openList[_rows][_colls];
    int closeList[_rows][_colls];
    int dirMap[_rows][_colls];
    std::priority_queue<Node> listNode;
    int di[4] = {1, 0, -1, 0};
    int dj[4] = {0, 1, 0, -1};
    int x = 0, y = 0;
    
    if (_map[i1][j1] == WALL || _map[i2][j2] == WALL) {
        return false;
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _colls; j++) {
            openList[i][j] = 0;
            closeList[i][j] = 0;
        }
    }
    Node n0(i1, j1, 0, 0);
    n0.updateF(i2, j2);
    listNode.push(n0);
    openList[i1][j1] = n0._F;
    
    while (!listNode.empty()) {
        x = listNode.top()._x;
        y = listNode.top()._y;
        listNode.pop();
        openList[x][y] = 0;
        closeList[x][y] = 1;
        
        if (x == i2 && y == j2) {
            while (!(x == i1 && y == j1)) {
                int j = dirMap[x][y];
                _wayY[_lengthWay] = x;
                _wayX[_lengthWay] = y;
                _lengthWay++;
                x += di[j];
                y += dj[j];
            }
            _wayY[_lengthWay] = i1;
            _wayX[_lengthWay] = j1;
        }
        
        for (int k = 0; k < countDir; k++) {
            int ix = x + di[k], jy = y + dj[k];
            if (ix < _rows && ix >= 0 && jy < _colls && jy >= 0 && _map[ix][jy] == WAY && closeList[ix][jy] != 1) {
                Node m0(ix, jy, 0, 0);
                m0.nextLevel();
                m0.updateF(i2, j2);
                
                if (openList[ix][jy] == 0) {
                    openList[ix][jy] = m0._F;
                    listNode.push(m0);
                    dirMap[ix][jy] = (k + countDir / 2) % countDir;
                } else if (openList[ix][jy] > m0._F) {
                    openList[ix][jy] = m0._F;
                    dirMap[ix][jy] = (k + countDir / 2) % countDir;
                }
            }
        }
    }
    if (x != i2 && y != j2)
        return false;
    
    return true;
}

void CBlinkyGhost::printWay()
{
    std::cout << "WAY" << std::endl;
    for (int i = 0; i < _lengthWay + 1; i++) {
        std::cout << _wayY[i] << " " << _wayX[i] << std::endl;
    }
}
