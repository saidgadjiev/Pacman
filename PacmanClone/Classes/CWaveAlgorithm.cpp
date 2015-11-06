//
//  CWaveAlgorithm.cpp
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#include "CWaveAlgorithm.h"

void CWaveAlgorithm::deleteMap()
{
    for (int i = 0; i < _rows; i++) {
        delete [] _map[i];
    }
    _map = nullptr;
}

void CWaveAlgorithm::initMap(int **map, int rows, int colls)
{
    newMap(rows, colls);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _colls; j++) {
            if (map[i][j] == 0) {
                _map[i][j] = -1;
            } else {
                _map[i][j] = -2;
            }
        }
    }
}

void CWaveAlgorithm::newMap(int rows, int colls)
{
    _rows = rows;
    _colls = colls;
    _map = new int*[_rows];
    
    for (int i = 0; i < _rows; i++) {
        _map[i] = new int[_colls];
    }
}

bool CWaveAlgorithm::findWay(int *nextY, int *nextX, int i1, int j1, int i2, int j2)
{
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
    int _wayY[d + 1];
    int _wayX[d + 1];
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
    *nextX = _wayX[1];
    *nextY = _wayY[1];
    
    return true;
}