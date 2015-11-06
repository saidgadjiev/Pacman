//
//  CInkyGhost.h
//  PacmanClone
//
//  Created by Саид on 05.09.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CInkyGhost__
#define __PacmanClone__CInkyGhost__

#include "CSprite.h"

class CInkyGhost: public CSprite {
public:
    CInkyGhost();
    void changeNewDirection();
private:
};

#endif /* defined(__PacmanClone__CInkyGhost__) */
