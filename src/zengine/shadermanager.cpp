#include "shadermanager.h"

ShaderManager* ShaderManager::mShaderManager = nullptr;

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
    mShaderCache.clear();
}

Shader ShaderManager::getShaderProgram(GLchar* vertexPath, GLchar* fragmentPath)
{
    for (auto i = mShaderCache.begin(); i != mShaderCache.end(); ++i)
    {
        if (i->vertexPath == vertexPath && i->fragmentPath == fragmentPath)
        {
            return i->shader;
        }
    }

    Shader shader = Shader(vertexPath, fragmentPath);
    mShaderCache.push_back(ShaderNode(vertexPath, fragmentPath, shader));

    return shader;
}

ShaderManager* ShaderManager::getInstance()
{
    if (!mShaderManager)
    {
        mShaderManager = new ShaderManager();
    }
    return mShaderManager;
}