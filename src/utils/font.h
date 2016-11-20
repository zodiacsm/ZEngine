//
//  font.h
//  GlewTest
//
//  Created by 施铭 on 16/11/2.
//  Copyright © 2016年 施铭. All rights reserved.
//

#ifndef FONT_H
#define FONT_H

#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#include "../shader.h"
#include <string>
#include <glew/glew.h>

// GLFW
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

struct CellPosition {
    CellPosition(char r, char c) : row(r), col(c)
    {
        
    }
    
    char row;
    char col;
};

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
    
    CellPosition cellPosition;
};

struct FontInfo {
    GLfloat verteies[6][4];
    GLuint textureID;
};

class Font
{
private:
    Font();
    
public:
    static Font* getInstance();

public:
    void init();
    
//    void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    
    void submit(const FontInfo &fontInfo);
    
    std::map<GLuint, Character> getCharacters();
    
    Character getCharacter(GLuint index);
    
    CellPosition getUnUsedCellPosition();
    
    GLuint getFontTextureID(){return mFontTextureCache;};
    
private:
    std::map<GLuint, Character> mCharacters;
    
    static Font* mFont;
    
    GLuint mFontTextureCache;
    
    char* mCellInfos;
    
    FT_Library ft;
    FT_Face face;
    
    char mRowIndex;
};




#endif /* font_h */
