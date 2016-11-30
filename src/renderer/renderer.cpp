//
//  renderer.cpp
//  GlewTest
//
//  Created by 施铭 on 16/11/7.
//  Copyright © 2016年 施铭. All rights reserved.
//

#include <stdio.h>
#include "renderer.h"
#include "../utils/font.h"
#include "../shadermanager.h"

Renderer* Renderer::mRenderer = nullptr;

//max character
static const int MAX_CHARACTER = 1024;

GLfloat cubeVertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint cubeIndices[] = {
    0, 3, 1,
    1, 3, 2
};

Renderer::Renderer()
{
    
}

Renderer* Renderer::getInstance()
{
    if (!mRenderer)
    {
        mRenderer = new Renderer();
        mRenderer->init();
    }
    return mRenderer;
}

void Renderer::init()
{
    glGenVertexArrays(1, &mFontVAO);
    glGenBuffers(1, &mFontVBO);
    
    glBindVertexArray(mFontVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mFontVBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4 * MAX_CHARACTER, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &mCubeVAO);
    glGenBuffers(1, &mCubeVBO);
    glGenBuffers(1, &mCubeEBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(mCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer::submit(const FontInfo &fontInfo)
{
    mFontInfos.push_back(fontInfo);
}

void Renderer::render()
{
    renderScene();

    renderText();
}

void Renderer::renderText()
{
    shader = ShaderManager::getInstance()->getShaderProgram("text.vs", "text.frag");
    shader.Use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Activate corresponding render state
    glUniform3f(glGetUniformLocation(shader.Program, "textColor"), 255, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mFontVAO);

    for (int i = 0; i < mFontInfos.size() && i < MAX_CHARACTER; ++i)
    {
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, Font::getInstance()->getFontTextureID());
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, mFontVBO);
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(GLfloat)* 6 * 4, sizeof(GLfloat)* 6 * 4, mFontInfos[i].verteies);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6 * mFontInfos.size());

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    mFontInfos.clear();
}

void Renderer::renderScene()
{
    shader = ShaderManager::getInstance()->getShaderProgram("cube.vs", "cube.frag");
    shader.Use();

    glBindVertexArray(mCubeVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
