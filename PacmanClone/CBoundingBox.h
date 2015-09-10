//
//  PBoundingBox.h
//  Pacman
//
//  Created by Саид on 26.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __Pacman__PBoundingBox__
#define __Pacman__PBoundingBox__

typedef struct {
    int top;
    int bottom;
    int left;
    int right;
}CBoundingBox;

CBoundingBox makeBoundingBox(int top, int bottom, int left, int right);
#endif /* defined(__Pacman__PBoundingBox__) */
