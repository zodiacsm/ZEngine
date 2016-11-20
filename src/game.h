//
//  game.hpp
//  GlewTest
//
//  Created by 施铭 on 16/10/31.
//  Copyright © 2016年 施铭. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <string>
#include "shader.h"
#include "camera.h"

class Game
{
private:
    Game();
    
public:
    static Game* getInstance();
    
    void update();
    
    //render the game
    void render();
    
    //accept user input
    void input();
    
    //init
    void init();
    
public:
    GLFWwindow* initWindow(GLuint width, GLuint height, const std::string &title);
    
private:
    static Game *mGame;
    
    GLuint VBO, containerVAO;
    
    GLuint lightVAO;
    
    Shader lightingShader;
    
    Camera  camera;
};

#endif /* game_hpp */
