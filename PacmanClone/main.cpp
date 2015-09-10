//
//  main.cpp
//  PacmanClone
//
//  Created by Саид on 27.08.15.
//  Copyright (c) 2015 Саид. All rights reserved.
//

#include "Prefix.h"
#include "CGameScene.h"
#define FPS 60

int main(int argc, const char * argv[]) {
    
    if (!glfwInit()) {
        std::cerr << "Error init glfw!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    CGameScene *gameScene = new CGameScene();
    
    gameScene->create(1024, 768, "Pacman Game", nullptr, nullptr);
    gameScene->init();
    double lastTime = glfwGetTime();
    double deltaTime = 0.f;
    while (!gameScene->getWindowState()) {
        gameScene->render();
        glfwPollEvents();
        deltaTime += (glfwGetTime() - lastTime) * FPS;
        lastTime = glfwGetTime();
        while (deltaTime >= 1.f) {
            gameScene->update();
            deltaTime--;
        }
        gameScene->setWindowState(glfwWindowShouldClose(gameScene->getWindow()));
    }
    delete gameScene;
    
    glfwTerminate();
    return 0;
}
