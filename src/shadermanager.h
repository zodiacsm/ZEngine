#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#define GLEW_STATIC
#include <glew/glew.h>
#include "shader.h"
#include <vector>

struct ShaderNode
{
    ShaderNode(GLchar *vp, GLchar *fp, Shader s)
    {
        vertexPath = vp;
        fragmentPath = fp;
        shader = s;
    }

    GLchar *vertexPath;
    GLchar *fragmentPath;
    Shader shader;
};

class ShaderManager
{
private:
    ShaderManager();

public:
    static ShaderManager* getInstance();

    ~ShaderManager();

    Shader getShaderProgram(GLchar* vertexPath, GLchar* fragmentPath);

private:
    std::vector<ShaderNode> mShaderCache;

    static ShaderManager* mShaderManager;
};

#endif