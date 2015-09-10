//
//  CSprite.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CSprite.h"

CSprite::CSprite():
    _position(makeVector2(528.f, 720.f)),
    _direction(STOP),
    _rotation(0.f),
    _velocity(0.f),
    _texture(nullptr),
    _animationTextureCoord(0.f),
    _animationTime(0)
{}

CSprite::~CSprite()
{
    delete _texture;
}

void CSprite::create(const std::string filename)
{
    _texture = new CTexture();
    _texture->loadTextureFromFile(filename);
}

void CSprite::setCenterPosition(GLfloat x, GLfloat y)
{
    _position.x = x;
    _position.y = y;
}

void CSprite::setCenterPosition(CVector2 position)
{
    _position = position;
}

CVector2 CSprite::getCenterPosition() const
{
    return _position;
}

void CSprite::setRotation(GLfloat rotation)
{
    _rotation = rotation;
}

GLfloat CSprite::getRotation() const
{
    return _rotation;
}

void CSprite::setTextureCoord(GLfloat textureCoord)
{
    _animationTextureCoord = textureCoord;
}

void CSprite::setVBOData()
{
    VBOData vertices[4] = {
        {{-SQUARE_SIZE / 2.f, -SQUARE_SIZE / 2.f, 0.f}, {0.5f - _animationTextureCoord, 0.f}},
        {{-SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f, 0.f}, {0.5f - _animationTextureCoord, 1.f}},
        {{SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f, 0.f}, {1.f - _animationTextureCoord, 1.f}},
        {{SQUARE_SIZE / 2.f, -SQUARE_SIZE / 2.f, 0.f}, {1.f - _animationTextureCoord, 0.f}}
    };

    for (int i = 0; i < 4; i++) {
        _vertices[i] = vertices[i];
    }
}


void CSprite::getNextPositionSquare(CVector2 *positionFirst, CVector2 *positionSecond) const
{
    *positionFirst = _position;
    *positionSecond = _position;
    
    if (_direction == LEFT) {
        positionFirst->x = _position.x - SQUARE_SIZE / 2.f - _velocity;
        positionFirst->y = _position.y - SQUARE_SIZE / 2.f + 0.1f;
        positionSecond->x = _position.x - SQUARE_SIZE / 2.f - _velocity;
        positionSecond->y = _position.y + SQUARE_SIZE / 2.f - 0.1f;
    }
    if (_direction == RIGHT) {
        positionFirst->x = _position.x + SQUARE_SIZE / 2.f;
        positionFirst->y = _position.y - SQUARE_SIZE / 2.f + 0.1f;
        positionSecond->x = _position.x + SQUARE_SIZE / 2.f;
        positionSecond->y = _position.y + SQUARE_SIZE / 2.f - 0.1f;
    }
    if (_direction == UP) {
        positionFirst->x = _position.x - SQUARE_SIZE / 2.f + 0.1f;
        positionFirst->y = _position.y - SQUARE_SIZE / 2.f - _velocity;
        positionSecond->x = _position.x + SQUARE_SIZE / 2.f - 0.1f;
        positionSecond->y = _position.y - SQUARE_SIZE / 2.f - _velocity;
    }
    if (_direction == DOWN) {
        positionFirst->x = _position.x - SQUARE_SIZE / 2.f + 0.1f;
        positionFirst->y = _position.y + SQUARE_SIZE / 2.f;
        positionSecond->x = _position.x + SQUARE_SIZE / 2.f - 0.1f;
        positionSecond->y = _position.y + SQUARE_SIZE / 2.f;
    }
}

void CSprite::getCenterPositionSideSquare(CVector2 *position) const
{
    *position = _position;
    
    if (_direction == LEFT) {
        position->x = _position.x + SQUARE_SIZE / 2 - _velocity;
    }
    if (_direction == RIGHT) {
        position->x = _position.x - SQUARE_SIZE / 2;
    }
    if (_direction == UP) {
        position->y = _position.y + SQUARE_SIZE / 2 - _velocity;
    }
    if (_direction == DOWN) {
        position->y = _position.y - SQUARE_SIZE / 2;
    }
}

void CSprite::setDirection(EDirection direction)
{
    _direction = direction;
}

EDirection CSprite::getDirection() const
{
    return _direction;
}

void CSprite::stopAnimate()
{
    _animationTextureCoord = 0.f;
}

void CSprite::startAnimate()
{
    if (_animationTime >= 5) {
        if (_animationTextureCoord == 0.5f) {
            _animationTextureCoord = 0.f;
        } else {
            _animationTextureCoord = 0.5f;
        }
        _animationTime = 0;
    }
    _animationTime++;
}

void CSprite::render()
{
    glLoadIdentity();
    glTranslatef(_position.x, _position.y, 0.f);
    glRotatef(_rotation, 0.f, 0.f, 1.f);
    setVBOData();
    _texture->setVBOData(_vertices);
    _texture->setBindtexture();
    _texture->render(1);
}


void CSprite::moveLeft()
{
    _position.x -= _velocity;
}

void CSprite::moveUp()
{
    _position.y -= _velocity;
}

void CSprite::moveRight()
{
    _position.x += _velocity;
}

void CSprite::moveDown()
{
    _position.y += _velocity;
}

void CSprite::move()
{
    switch (_direction) {
        case LEFT:
            moveLeft();
            break;
        case RIGHT:
            moveRight();
            break;
        case UP:
            moveUp();
            break;
        case DOWN:
            moveDown();
            break;
        default:
            break;
    }
}

