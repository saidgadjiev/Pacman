//
//  CFactory.h
//  PacmanClone
//
//  Created by Саид on 06.11.15.
//  Copyright © 2015 Саид. All rights reserved.
//

#ifndef CFactory_h
#define CFactory_h

#include "CSprite.h"
#include "CBlinkyGhost.h"
#include "CInkyGhost.h"
#include "CPacman.h"
#include "CLevel.h"
#include "CWaveAlgorithm.h"
#include <iostream>
#include <cstring>

class CFactory {
public:
    static CFactory *getInstance();
    CBlinkyGhost *createBlinkyGhost(CLevel *level);
    CInkyGhost *createInkyGhost();
    CPacman *createPacman();
    CLevel *createLevel(std::string filename, int windowWidth, int windowHeight);
private:
    CFactory() {}
    static CFactory *instance;
};

#endif /* CFactory_h */
