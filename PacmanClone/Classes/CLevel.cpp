//
//  CLevel.cpp
//  PacmanClone
//
//  Created by Саид on 28.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CLevel.h"
#include <unistd.h>

CLevel::CLevel():
    _wall(nullptr),
    _food(nullptr),
    _map(nullptr),
    _rows(0),
    _colls(0),
    _wallCount(0),
    _foodCount(0),
    _timeCheckCrossRoad(0)
{}

CLevel::~CLevel()
{
    for (int i = 0; i < _rows; i++) {
        delete []_map[i];
    }
    delete _wall;
    delete _food;
    _rows = 0;
    _colls = 0;
    _wallCount = 0;
    _foodCount = 0;
}

void CLevel::loadFromFile(const std::string filename)
{
    Tmx::Map *map = new Tmx::Map();
    
    map->ParseFile(filename);
    if (map->HasError()) {
        std::cout << "Error :" << map->GetErrorText().c_str() << std::endl;
        
        exit(EXIT_FAILURE);
    }
    loadTextureTiles(map);
    loadMap(map);
    
}

void CLevel::loadMap(Tmx::Map *map )
{
    for (int i = 0; i < map->GetNumTileLayers(); i++) {
        const Tmx::TileLayer *tileLayer = map->GetTileLayer(i);
        for (int y = 0; y < tileLayer->GetHeight(); y++) {
            for (int x = 0; x < tileLayer->GetWidth(); x++) {
                if (tileLayer->GetTileTilesetIndex(x, y) != -1) {
                    _map[y][x] = tileLayer->GetTileTilesetIndex(x, y);
                }
            }
        }
    }
}

void CLevel::loadTextureTiles(Tmx::Map *map)
{
    const Tmx::Tileset *tilesetWall = map->GetTileset(0);
    CTexture *textureWall = new CTexture();
    
    textureWall->loadTextureFromFile(tilesetWall->GetImage()->GetSource());
    _wall = textureWall;
    const Tmx::Tileset *tilesetFood = map->GetTileset(1);
    CTexture *textureFood = new CTexture();
    
    textureFood->loadTextureFromFile(tilesetFood->GetImage()->GetSource());
    _food = textureFood;
}

void CLevel::deleteFood(int y, int x)
{
    _map[y][x] = -1;
}

void CLevel::initMap(int rows, int colls)
{
    _map = new int*[rows];
    _rows = rows;
    _colls = colls;
    
    for (int i = 0; i < _rows; i++) {
        _map[i] = new int[_colls];
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _colls; j++) {
            _map[i][j] = -1;
        }
    }
}

int **CLevel::getMap() const
{
    return _map;
}

int CLevel::getMapColls() const
{
    return _colls;
}

int CLevel::getMapRows() const
{
    return _rows;
}

bool CLevel::isCrossRoad(CSprite *sprite) const
{
    CVector2 position = sprite->getCenterPosition();
    int x = position.x / SQUARE_SIZE;
    int y = position.y / SQUARE_SIZE;
    EDirection direction = sprite->getDirection();
    int xPos = position.x;
    int yPos = position.y;
    
    if ((yPos + 16) % 32 == 0 && (xPos + 16) % 32 == 0) {
        switch (direction) {
            case LEFT: case RIGHT:
                if (_map[y - 1][x] != 0) {
                    return true;
                }
                if (_map[y + 1][x] != 0) {
                    return true;
                }
                break;
            case UP: case DOWN:
                if (_map[y][x + 1] != 0) {
                    return true;
                }
                if (_map[y][x - 1] != 0) {
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

void CLevel::setVBOWall(int deltaVertWall, int x, int y)
{
    _verticesWall[0 + deltaVertWall] = {{0.f + x * SQUARE_SIZE, 0.f + y * SQUARE_SIZE, 0.f}, {0.f, 0.f}};
    _verticesWall[1 + deltaVertWall] = {{0.f + x * SQUARE_SIZE, (SQUARE_SIZE + y * SQUARE_SIZE) * 1.f, 0.f}, {0.f, 1.f}};
    _verticesWall[2 + deltaVertWall] = {{1.f * (SQUARE_SIZE + x * SQUARE_SIZE), 1.f * (SQUARE_SIZE + y * SQUARE_SIZE), 0.f}, {1.f, 1.f}};
    _verticesWall[3 + deltaVertWall] = {{1.f * (SQUARE_SIZE + x * SQUARE_SIZE), 0.f + y * SQUARE_SIZE, 0.f}, {1.f, 0.f}};
}

void CLevel::setVBOFood(int deltaVertFood, int x, int y)
{
    _verticesFood[0 + deltaVertFood] = {{0.f + x * SQUARE_SIZE, 0.f + y * SQUARE_SIZE, 0.f}, {0.f, 0.f}};
    _verticesFood[1 + deltaVertFood] = {{0.f + x * SQUARE_SIZE, (SQUARE_SIZE + y * SQUARE_SIZE) * 1.f, 0.f}, {0.f, 1.f}};
    _verticesFood[2 + deltaVertFood] = {{1.f * (SQUARE_SIZE + x * SQUARE_SIZE), 1.f * (SQUARE_SIZE + y * SQUARE_SIZE), 0.f}, {1.f, 1.f}};
    _verticesFood[3 + deltaVertFood] = {{1.f * (SQUARE_SIZE + x * SQUARE_SIZE), 0.f + y * SQUARE_SIZE, 0.f}, {1.f, 0.f}};
}

void CLevel::setVBOData()
{
    _wallCount = 0;
    _foodCount = 0;
    int deltaVertWall = 0, deltaVertFood = 0;
    for (int y = 0; y < _rows; y++) {
        for (int x = 0; x < _colls; x++) {
            if (_map[y][x] == 0) {
                setVBOWall(deltaVertWall, x, y);
                deltaVertWall += 4;
                ++_wallCount;
            }
            if (_map[y][x] == 1) {
                setVBOFood(deltaVertFood, x, y);
                deltaVertFood += 4;
                ++_foodCount;
            }
        }
    }
}

void CLevel::render()
{
    glLoadIdentity();
    setVBOData();
    _wall->setVBOData(_verticesWall);
    _wall->setBindtexture();
    _wall->render(_wallCount);
    _food->setVBOData(_verticesFood);
    _food->setBindtexture();
    _food->render(_foodCount);
}