//
//  CInkyGhost.cpp
//  PacmanClone
//
//  Created by Саид on 05.09.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CInkyGhost.h"

CInkyGhost::CInkyGhost():
    CSprite()
{}

void CInkyGhost::changeNewDirection()
{
    switch (arc4random() % 4) {
        case 0:
            _direction = LEFT;
            break;
        case 1:
            _direction = RIGHT;
            break;
        case 2:
            _direction = UP;
            break;
        case 3:
            _direction = DOWN;
            break;
        default:
            break;
    }
}
