#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <glew/glew.h>

// GLFW
#include <glfw/glfw3.h>

// Other Libs
#include "stb_image.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "utils/time.h"
#include "game.h"
#include "utils/font.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void float2str(const float &float_temp, std::string &string_temp);

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
//GLfloat lastX  =  WIDTH / 2.0f;
//GLfloat lastY  =  HEIGHT / 2.0f;
bool    keys[1024];

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


//The MAIN function, from here we start the application and run the game loop
int main()
{
    GLFWwindow* window = Game::getInstance()->initWindow(800, 600, "Zodiac Engine");
    
    Game::getInstance()->init();
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    float lastTime = Time::getCurrentTime();
    
    static float frame = 30;
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check and call events
        glfwPollEvents();
        
        // Clear the colorbuffer
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
        
        float startTime = Time::getInstance()->getCurrentTime();
        float deltaTime = startTime - lastTime;
        
//        if (deltaTime < 1.0f / frame) {
//            continue;
//        }
        
        float renderTime = startTime - lastTime;
        lastTime = startTime;
        std::cout << "renderTime" << renderTime << std::endl;
        std::cout << "frameTime" << 1.0f / renderTime << std::endl;

        std::string strFrame = "";
        float2str(1.0f / renderTime, strFrame);
        //Font::getInstance()->init();
        //Font::getInstance()->RenderText(std::string("1234"), 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        Font::getInstance()->RenderText(strFrame, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        //Font::getInstance()->RenderText(, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        
        Game::getInstance()->render();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
//    if (keys[GLFW_KEY_W])
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (keys[GLFW_KEY_S])
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (keys[GLFW_KEY_A])
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (keys[GLFW_KEY_D])
//        camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//    
//    GLfloat xoffset = xpos - lastX;
//    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//    
//    lastX = xpos;
//    lastY = ypos;
//    
//    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}

void float2str(const float &float_temp, std::string &string_temp)
{
    std::stringstream stream;
    stream << float_temp;
    string_temp = stream.str();   //此处也可以用 stream>>string_temp  
}