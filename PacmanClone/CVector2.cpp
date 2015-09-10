//
//  Vector2.cpp
//  Pacman
//
//  Created by Саид on 25.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CVector2.h"

CVector2 makeVector2(GLfloat x, GLfloat y)
{
    CVector2 newVector;
    
    newVector.x = x;
    newVector.y = y;
    
    return newVector;
}

CVector2 addVector2(CVector2 first, CVector2 second)
{
    CVector2 newVector;
    
    newVector.x = first.x + second.x;
    newVector.y = first.y + second.y;
    
    return newVector;
}