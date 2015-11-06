//
//  CLevel.h
//  PacmanClone
//
//  Created by Саид on 28.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CLevel__
#define __PacmanClone__CLevel__

#include "Prefix.h"
#include "CTexture.h"
#include "CSprite.h"
#include <TmxParser/Tmx.h>
#include <vector>

class CLevel {
public:
    CLevel();
    ~CLevel();
    void loadFromFile(const std::string filename);
    void setVBOData();
    void render();
    void initMap(int rows, int calls);
    void deleteFood(int y, int x);
    int **getMap() const;
    int getMapRows() const;
    int getMapColls() const;
    bool isCrossRoad(CSprite *sprite) const;
private:
    void setVBOWall(int deltaVertWall, int x, int y);
    void setVBOFood(int deltaVertFood, int x, int y);
    void loadMap(Tmx::Map *map);
    void loadTextureTiles(Tmx::Map *map);
    VBOData _verticesWall[3072];
    VBOData _verticesFood[3072];
    CTexture *_wall;
    CTexture *_food;
    int **_map;
    int _rows;
    int _colls;
    int _wallCount;
    int _foodCount;
    int _timeCheckCrossRoad;
};

#endif /* defined(__PacmanClone__CLevel__) */
