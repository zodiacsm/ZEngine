//
//  renderer.h
//  GlewTest
//
//  Created by 施铭 on 16/11/7.
//  Copyright © 2016年 施铭. All rights reserved.
//

#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <glew/glew.h>

// GLFW
#include <glfw/glfw3.h>

#include <vector>
#include "../shader.h"
#include "../utils/font.h"

struct FontInfo;

class Renderer
{
public:
    static Renderer* getInstance();
    
private:
    Renderer();
    
public:
    void init();
    
    void render();
    
    void submit(const FontInfo &fontInfo);

private:
    void renderText();

    void renderScene();

    void renderCubes();

    void renderImage();
    
private:
    GLuint mFontVAO, mFontVBO;
    
    static Renderer *mRenderer;
    
    std::vector<FontInfo> mFontInfos;
    
    Shader shader;

	Shader imageShader;

    GLuint mCubeVBO, mCubeVAO, mCubeEBO;

    GLuint texture1;
    GLuint texture2;

    GLuint mcubesVBO, mcubesVAO;

	GLuint mImageVBO, mImageVAO;

	GLuint mLogoTexture;
};


#endif /* renderer_h */
