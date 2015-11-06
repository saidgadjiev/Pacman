//
//  CTexture.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CTexture.h"

CTexture::CTexture():
    _textureID(0),
    _textureWidth(0),
    _textureHeight(0)
{
    initIL();
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &_textureID);
}

void CTexture::loadTextureFromFile(const std::string filename)
{
    ILuint imgID = 0;
    
    ilGenImages(1, &imgID);
    ilBindImage(imgID);
    ILboolean success = ilLoadImage(filename.c_str());
    if (success == IL_FALSE) {
        std::cout << "Error open image :" << filename;
        exit(EXIT_FAILURE);
    }
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    
    loadTextureFromPixel((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
    
    ilDeleteImages(1, &imgID);
}

void CTexture::loadTextureFromPixel(GLuint *pixels, GLuint width, GLuint height)
{
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, NULL);
    
    _textureWidth = width;
    _textureHeight = height;
}

void CTexture::setBindtexture()
{
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void CTexture::setVBOData(VBOData vertices[])
{
    for (int i = 0; i < 3072; i++) {
        _vertices[i] = vertices[i];
    }
}

void CTexture::initIL()
{
    ilInit();
    ilClearColour(255, 255, 255, 000);
}

void CTexture::initVBO()
{
    glGenBuffers(1, &_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VBOData), (GLvoid *)offsetof(VBOData, positionCoordinates));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VBOData), (GLvoid *)offsetof(VBOData, textureCoordinates));
}

void CTexture::render(int countDrawObjec)
{
    initVBO();
    glDrawArrays(GL_QUADS, 0, countDrawObjec * 4);
}

