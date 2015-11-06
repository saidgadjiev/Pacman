//
//  CGameScene.h
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CGameScene__
#define __PacmanClone__CGameScene__

#include "Prefix.h"
#include "CScene.h"
#include "CPacman.h"
#include "CLevel.h"
#include "CInkyGhost.h"
#include "CBlinkyGhost.h"
#include "CFactory.h"

class CGameScene: public CScene {
public:
    CGameScene();
    ~CGameScene();
    void render();
    void init();
    void update();
    void checkOutOfScreen(CSprite *sprite);
    bool isCollisionWithWall(CSprite *sprite);
    void setCorrectDirectionAndRotationForPacman();
    void collisionDetectionWithFood();
    void correctPosition(CVector2 *position);
    void collisionDetectionPacmanWithGhost();
private:
    void keyHundler();
    CPacman *_pacman;
    CInkyGhost *_inky;
    CBlinkyGhost *_blinky;
    CLevel *_level;
};
#endif /* defined(__PacmanClone__CGameScene__) */
