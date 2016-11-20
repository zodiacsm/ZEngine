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

Renderer* Renderer::mRenderer = nullptr;

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
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    shader = Shader("text.vs", "text.frag");
    shader.Use();
}

void Renderer::submit(const FontInfo &fontInfo)
{
    mFontInfos.push_back(fontInfo);
}

void Renderer::render()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    // Activate corresponding render state
    glUniform3f(glGetUniformLocation(shader.Program, "textColor"), 255, 0, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mFontVAO);
    
    for (int i = 0; i < mFontInfos.size(); ++i)
    {
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, Font::getInstance()->getFontTextureID());
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, mFontVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*24, mFontInfos[i].verteies); // Be sure to use glBufferSubData and not glBufferData
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    mFontInfos.clear();
}
