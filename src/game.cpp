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
    glfwPollEvents();
    //do_movement();
    
    // Clear the colorbuffer
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    // Use cooresponding shader when setting uniforms/drawing objects
//    lightingShader.Use();
//    GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
//    GLint lightColorLoc  = glGetUniformLocation(lightingShader.Program, "lightColor");
//    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
//    glUniform3f(lightColorLoc,  1.0f, 0.5f, 1.0f);
//    
//    // Create camera transformations
//    glm::mat4 view;
//    view = camera.GetViewMatrix();
//    glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
//    // Get the uniform locations
//    GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
//    GLint viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
//    GLint projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
//    // Pass the matrices to the shader
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//    
//    // Draw the container (using container's vertex attributes)
//    glBindVertexArray(containerVAO);
//    glm::mat4 model;
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
    
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
    
//    // Build and compile our shader program
//    lightingShader = Shader("lighting.vs", "lighting.frag");
//    
//    // Set up vertex data (and buffer(s)) and attribute pointers
//    GLfloat vertices[] = {
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        
//        -0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f, -0.5f,
//        
//        -0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f
//    };
//    // First, set the container's VAO (and VBO)
//    
//    glGenVertexArrays(1, &containerVAO);
//    glGenBuffers(1, &VBO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    glBindVertexArray(containerVAO);
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
//    
//    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
//    
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // Set the vertex attributes (only position data for the lamp))
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
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
