//
//  CScene.h
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#ifndef __PacmanClone__CScene__
#define __PacmanClone__CScene__

#include "Prefix.h"

class CScene {
public:
    CScene();
    virtual ~CScene();
    void destroyWindow();
    void create(GLfloat width, GLfloat height, std::string title, GLFWmonitor *monitor, GLFWwindow *share);
    GLFWwindow *getWindow() const;
    void setWindowState(bool state);
    bool getWindowState() const;
    void makeWindowCurrent();
    virtual void render();
protected:
    bool _state;
    GLFWwindow *_window;
    GLfloat _width;
    GLfloat _height;
    std::string _title;
    GLFWmonitor *_monitor;
    GLFWwindow *_share;
    void initGL();
};

#endif /* defined(__PacmanClone__CScene__) */
