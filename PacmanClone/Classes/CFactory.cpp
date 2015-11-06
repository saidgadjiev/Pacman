//
//  CFactory.cpp
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#include "CFactory.h"

CFactory *CFactory::instance = nullptr;

CFactory *CFactory::getInstance() {
    if (instance == nullptr) {
        instance = new CFactory;
    }
    
    return instance;
}

CBlinkyGhost *CFactory::createBlinkyGhost(CLevel *level) {
    CBlinkyGhost *blinky = new CBlinkyGhost();
    
    blinky->setTextureCoord(0.f);
    blinky->create("../Sprites/Ghost.png");
    blinky->setVelocity(2.0f);
    blinky->setDirection(RIGHT);
    blinky->setCenterPosition(48, 48);
    CWaveAlgorithm *algorithm = new CWaveAlgorithm();
    algorithm->initMap(level->getMap(), level->getMapRows(), level->getMapColls());
    blinky->setStrategy(algorithm);
    
    return blinky;
}

CInkyGhost *CFactory::createInkyGhost() {
    CInkyGhost *inky = new CInkyGhost();
    
    inky->setTextureCoord(0.5f);
    inky->create("../Sprites/Ghost.png");
    inky->setVelocity(2.0f);
    inky->setDirection(RIGHT);
    inky->setCenterPosition(976, 48);
    
    return inky;
}

CPacman *CFactory::createPacman() {
    CPacman *pacman = CPacman::getInstance();
    
    pacman->create("../Sprites/Pacman.png");
    pacman->setVelocity(2.0f);
    pacman->setDirection(DOWN);
    
    return pacman;
}

CLevel *CFactory::createLevel(std::string filename, int windowWidth, int windowHeight) {
    CLevel *level = new CLevel();
    level = new CLevel();
    level->initMap(windowHeight / SQUARE_SIZE, windowWidth / SQUARE_SIZE);
    level->loadFromFile(filename);
    
    return level;
}
