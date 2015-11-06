//
//  CWaveAlgorithm.h
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#ifndef CWaveAlgorithm_h
#define CWaveAlgorithm_h

#include "CStrategyFindWay.h"

class CWaveAlgorithm: public CStrategyFindWay {
public:
    bool findWay(int *nextY, int *nextX, int i1, int j1, int i2, int j2);
    void initMap(int **map, int rows, int colls);
    ~CWaveAlgorithm() { deleteMap(); }
private:
    void newMap(int rows, int colls);
    void deleteMap();
    int **_map;
    int _rows;
    int _colls;
    int _lengthWay;
};

#endif /* CWaveAlgorithm_h */
