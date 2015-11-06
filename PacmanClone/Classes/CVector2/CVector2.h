//
//  Vector2.h
//  Pacman
//
//  Created by Саид on 25.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __Pacman__Vector2__
#define __Pacman__Vector2__

#include <GLFW/glfw3.h>

struct CVector2 {
    GLfloat x;
    GLfloat y;
};

CVector2 makeVector2(GLfloat x, GLfloat y);
CVector2 addVector2(CVector2 first, CVector2 second);

#endif /* defined(__Pacman__Vector2__) */
