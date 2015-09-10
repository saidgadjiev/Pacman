//
//  CSprite.h
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CSprite__
#define __PacmanClone__CSprite__

#include "Prefix.h"
#include "CTexture.h"

class CSprite {
public:
    CSprite();
    virtual ~CSprite();
    void setCenterPosition(CVector2 position);
    CVector2 getCenterPosition() const;
    void setCenterPosition(GLfloat x, GLfloat y);
    void getCenterPosition(GLfloat *x, GLfloat *y) const;
    void setRotation(GLfloat rotation);
    void setDirection(EDirection direction);
    EDirection getDirection() const;
    void setVelocity(GLfloat velocity);
    GLfloat getVelocity() const;
    GLfloat getRotation() const;
    void setTexture(CTexture *texture);
    CTexture *getTexture() const;
    void create(const std::string filename);
    void setTextureCoord(GLfloat textureCoord);
    void stopAnimate();
    void startAnimate();
    virtual void render();
    void moveLeft();
    void moveUp();
    void moveRight();
    void moveDown();
    virtual void move();
    void getNextPositionSquare(CVector2 *positionFirst, CVector2 *positionSecond) const;
    void getCenterPositionSideSquare(CVector2 *position) const;
protected:
    CVector2 _position;
    EDirection _direction;
    GLfloat _rotation;
    GLfloat _velocity;
private:
    void setVBOData();
    CTexture *_texture;
    GLfloat _animationTextureCoord;
    int _animationTime;
    VBOData _vertices[4];
};

#endif /* defined(__PacmanClone__CSprite__) */
