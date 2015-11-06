//
//  CGameScene.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CGameScene.h"

CGameScene::CGameScene() :
    CScene()
{}

CGameScene::~CGameScene()
{
    delete _inky;
    delete  _blinky;
    delete _level;
}

void CGameScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _level->render();
    _pacman->render();
    _inky->render();
    _blinky->render();
    glfwSwapBuffers(_window);
}

void CGameScene::update()
{
    keyHundler();
    setCorrectDirectionAndRotationForPacman();
    if (!isCollisionWithWall(_pacman)) {
        _pacman->startAnimate();
        _pacman->move();
    } else {
        _pacman->stopAnimate();
    }
    collisionDetectionWithFood();
    checkOutOfScreen(_pacman);
    
    _blinky->moveTo(_pacman->getCenterPosition());
    if (!isCollisionWithWall(_inky)) {
        _inky->move();
    } else {
        _inky->changeNewDirection();
    }
    
    if (_level->isCrossRoad(_inky)) {
        _inky->changeNewDirection();
    }
    checkOutOfScreen(_inky);
    collisionDetectionPacmanWithGhost();
    
}

void CGameScene::keyHundler()
{
    _pacman->setPrevDirection(_pacman->getDirection());
    _pacman->setPrevRotation(_pacman->getRotation());
    if (glfwGetKey(_window, GLFW_KEY_LEFT)) {
        _pacman->setRotation(-180.f);
        _pacman->setDirection(LEFT);
        _pacman->setNextRotation(-180.f);
        _pacman->setNextDirection(_pacman->getDirection());
    }
    if (glfwGetKey(_window, GLFW_KEY_RIGHT)) {
        _pacman->setRotation(0.f);
        _pacman->setDirection(RIGHT);
        _pacman->setNextRotation(0.f);
        _pacman->setNextDirection(_pacman->getDirection());
    }
    if (glfwGetKey(_window, GLFW_KEY_UP)) {
        _pacman->setRotation(-90.f);
        _pacman->setDirection(UP);
        _pacman->setNextRotation(-90.f);
        _pacman->setNextDirection(_pacman->getDirection());
    }
    if (glfwGetKey(_window, GLFW_KEY_DOWN)) {
        _pacman->setRotation(90.f);
        _pacman->setDirection(DOWN);
        _pacman->setNextRotation(90.f);
        _pacman->setNextDirection(_pacman->getDirection());
        
    }
    if (glfwGetKey(_window, GLFW_KEY_H)) {
        _pacman->setDirection(STOP);
    }
}

void CGameScene::checkOutOfScreen(CSprite *sprite)
{
    CVector2 correctPos = sprite->getCenterPosition();
    
    correctPosition(&correctPos);
    sprite->setCenterPosition(correctPos);
}

void CGameScene::init()
{
    CFactory *factory = CFactory::getInstance();
    
    _level = factory->createLevel("Levels/TestMao.tmx", _width, _height);
    _pacman = factory->createPacman();
    _inky = factory->createInkyGhost();
    _blinky = factory->createBlinkyGhost(_level);
}

void CGameScene::setCorrectDirectionAndRotationForPacman()
{
    EDirection prevDir = _pacman->getPrevDirection();
    GLfloat prevRotation = _pacman->getPrevRotation();
    
    if (isCollisionWithWall(_pacman)) {
        _pacman->setDirection(prevDir);
        _pacman->setRotation(prevRotation);
    }
    
    prevDir = _pacman->getDirection();
    prevRotation = _pacman->getRotation();
    _pacman->setDirection(_pacman->getNextDirection());
    _pacman->setRotation(_pacman->getNextRotation());
    
    if (isCollisionWithWall(_pacman)) {
        _pacman->setDirection(prevDir);
        _pacman->setRotation(prevRotation);
    }
}

bool CGameScene::isCollisionWithWall(CSprite *sprite)
{
    bool collision = false;
    int **map = _level->getMap();
    CVector2 firstCoord;
    CVector2 secondCoord;
    sprite->getNextPositionSquare(&firstCoord, &secondCoord);
    
    correctPosition(&firstCoord);
    if (firstCoord.x == _width) {
        firstCoord.x = _width - 0.1f;
    }
    
    if (firstCoord.y == _height) {
        firstCoord.y = _height - 0.1f;
    }
    correctPosition(&secondCoord);
    if (secondCoord.x == _width) {
        secondCoord.x = _width - 0.1f;
    }
    
    if (secondCoord.y == _height) {
        secondCoord.y = _height - 0.1f;
    }
    
    int xFirst = firstCoord.x / SQUARE_SIZE;
    int yFirst = firstCoord.y / SQUARE_SIZE;
    int xSecond = secondCoord.x / SQUARE_SIZE;
    int ySecond = secondCoord.y / SQUARE_SIZE;

    if (map[yFirst][xFirst] == 0 || map[ySecond][xSecond] == 0) {
        collision = true;
    }
    
    return collision;
}

void CGameScene::collisionDetectionWithFood()
{
    int **map = _level->getMap();
    CVector2 position = _pacman->getCenterPosition();
    
    correctPosition(&position);
    
    if (position.x == _width) {
        position.x = _width - 0.1f;
    }
    
    if (position.y == _height) {
        position.y = _height - 0.1f;
    }
    
    int x = position.x / SQUARE_SIZE;
    int y = position.y / SQUARE_SIZE;
    
    if (map[y][x] == 1) {
        _level->deleteFood(y, x);
    }
}

void CGameScene::collisionDetectionPacmanWithGhost()
{
    CVector2 positionPacman = _pacman->getCenterPosition();
    CVector2 positionGhost = _inky->getCenterPosition();
    
    int x = positionPacman.x / SQUARE_SIZE;
    int y = positionPacman.y / SQUARE_SIZE;
    int x1 = positionGhost.x / SQUARE_SIZE;
    int y1 = positionGhost.y / SQUARE_SIZE;
    
    if (x == x1 && y == y1) {
        exit(EXIT_FAILURE);
    }
    
    positionGhost = _blinky->getCenterPosition();

    x1 = positionGhost.x / SQUARE_SIZE;
    y1 = positionGhost.y / SQUARE_SIZE;
    
    if (x == x1 && y == y1) {
        exit(EXIT_FAILURE);
    }
}

void CGameScene::correctPosition(CVector2 *position)
{
    if (position->y >= _height) {
        position->y = 0.f;
    } else if (position->y <= 0.f) {
        position->y = _height;
    }
    
    if (position->x >= _width) {
        position->x = 0.f;
    } else if (position->x <= 0.f) {
        position->x = _width;
    }
}















