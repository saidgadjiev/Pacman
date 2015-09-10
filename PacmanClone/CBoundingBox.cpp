//
//  PBoundingBox.cpp
//  Pacman
//
//  Created by Саид on 26.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CBoundingBox.h"

CBoundingBox makeBoundingBox(int top, int bottom, int left, int right)
{
    CBoundingBox boundingBox;
    
    boundingBox.top = top;
    boundingBox.bottom = bottom;
    boundingBox.left = left;
    boundingBox.right = right;
    
    return boundingBox;
}