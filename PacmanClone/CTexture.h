//
//  CTexture.h
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CTexture__
#define __PacmanClone__CTexture__

#include "Prefix.h"
#include <IL/il.h>

#define SQUARE_SIZE 32

class CTexture {
public:
    CTexture();
    ~CTexture();
    void loadTextureFromFile(const std::string filename);
    void loadTextureFromPixel(GLuint *pixels, GLuint width, GLuint height);
    GLuint getTextureID() const;
    GLuint getTextureWidth() const;
    GLuint getTextureHeight() const;
    void setVBOData(VBOData vertices[]);
    void setBindtexture();
    void render(int countDrawObject);
private:
    void initIL();
    void initVBO();
    GLuint _textureID;
    GLuint _textureWidth;
    GLuint _textureHeight;
    GLuint _vertexBufferId;
    VBOData _vertices[3072];
};

#endif /* defined(__PacmanClone__CTexture__) */
