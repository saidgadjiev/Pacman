//
//  CPacman.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CPacman.h"

CPacman::CPacman():
    CSprite(),
    _nextDirection(RIGHT)
{}

void CSprite::setVelocity(GLfloat velocity)
{
    _velocity = velocity;
}

GLfloat CSprite::getVelocity() const
{
    return _velocity;
}

void CPacman::setNextDirection(EDirection nextDirection)
{
    _nextDirection = nextDirection;
}

EDirection CPacman::getNextDirection() const
{
    return _nextDirection;
}

void CPacman::setNextRotation(GLfloat rotation)
{
    _nextRotation = rotation;
}

GLfloat CPacman::getNextRotation() const
{
    return _nextRotation;
}

void CPacman::setPrevDirection(EDirection nextDirection)
{
    _prevDirection = nextDirection;
}

EDirection CPacman::getPrevDirection() const
{
    return _prevDirection;
}

void CPacman::setPrevRotation(GLfloat rotation)
{
    _prevRotation = rotation;
}

GLfloat CPacman::getPrevRotation() const
{
    return _prevRotation;
}


