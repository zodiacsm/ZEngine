//
//  game.cpp
//  GlewTest
//
//  Created by 施铭 on 16/10/31.
//  Copyright © 2016年 施铭. All rights reserved.
//

#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils/font.h"
#include "renderer/renderer.h"

using namespace std;
Game* Game::mGame = nullptr;

Game::Game()
{
    
}

void Game::render()
{
    //glfwPollEvents();
    
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer::getInstance()->render();
}

void Game::input()
{
    
}

void Game::update()
{
    
}

void Game::init()
{
    // OpenGL options
    glEnable(GL_DEPTH_TEST);
    
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    
    Renderer::getInstance()->init();
    Font::getInstance()->init();
}

GLFWwindow* Game::initWindow(GLuint width, GLuint height, const string &title)
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
//    // Set the required callback functions
//    glfwSetKeyCallback(window, key_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
    
    // GLFW Options
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
    
    
    int screenWidth, screenHeight;
    
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);
    
    return window;
}

Game* Game::getInstance()
{
    if (!mGame)
    {
        mGame = new Game();
    }
    return mGame;
}
