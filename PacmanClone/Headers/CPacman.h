//
//  CPacman.h
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CPacman__
#define __PacmanClone__CPacman__

#include "CSprite.h"

class CPacman: public CSprite {
public:
    static CPacman *getInstance();
    void setNextDirection(EDirection nextDirection);
    EDirection getNextDirection() const;
    void setNextRotation(GLfloat rotation);
    GLfloat getNextRotation() const;
    void setPrevDirection(EDirection nextDirection);
    EDirection getPrevDirection() const;
    void setPrevRotation(GLfloat rotation);
    GLfloat getPrevRotation() const;
private:
    CPacman();
    static CPacman *instance;
    EDirection _nextDirection;
    GLfloat _nextRotation;
    EDirection _prevDirection;
    GLfloat _prevRotation;
};

#endif /* defined(__PacmanClone__CPacman__) */
