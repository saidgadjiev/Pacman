//
//  CScene.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "CScene.h"

CScene::CScene():
    _state(false),
    _window(nullptr),
    _width(0.f),
    _height(0.f),
    _title(""),
    _monitor(nullptr),
    _share(nullptr)
{}

CScene::~CScene()
{
    _state = true;
    destroyWindow();
}

void CScene::destroyWindow()
{
    glfwDestroyWindow(_window);
    _window = nullptr;
    _width = 0.f;
    _height = 0.f;
    _title = "";
    _monitor = nullptr;
    _share = nullptr;
}

void CScene::create(GLfloat width, GLfloat height, std::string title, GLFWmonitor *monitor, GLFWwindow *share)
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    _window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
    if (!_window) {
        glfwTerminate();
        std::cerr << "Error create window!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    _width = width;
    _height = height;
    _title = title;
    _monitor = monitor;
    _share = share;
    
    glfwMakeContextCurrent(_window);
    initGL();

}

GLFWwindow *CScene::getWindow() const
{
    return _window;
}

void CScene::setWindowState(bool state)
{
    _state = state;
}

bool CScene::getWindowState() const
{
    return _state;
}

void CScene::makeWindowCurrent()
{
    glfwMakeContextCurrent(_window);
}

void CScene::initGL()
{
    glViewport(0.f, 0.f, _width, _height);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.f, _width, _height, 0.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
}

void CScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(_window);
}

