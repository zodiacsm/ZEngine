//
//  font.cpp
//  GlewTest
//
//  Created by 施铭 on 16/11/2.
//  Copyright © 2016年 施铭. All rights reserved.
//

#include <stdio.h>
#include "font.h"
#include <iostream>
#include "../renderer/renderer.h"

static const int TEXTURE_WIDTH = 1024;

static const int TEXTURE_HEIGHT = 1024;

//size of a font character
static const int CHARACTER_CELL_SIZE = 64;

static const int WIDTH_SIZE = TEXTURE_WIDTH / CHARACTER_CELL_SIZE;

static const int HEIGHT_SIZE = TEXTURE_HEIGHT / CHARACTER_CELL_SIZE;

static const float CELL_RADIO = (float)CHARACTER_CELL_SIZE / TEXTURE_HEIGHT;

Font* Font::mFont = nullptr;

Font::Font():
 mFontTextureCache(0),
 mCellInfos(nullptr),
 mRowIndex(0)
{
    
}

Font* Font::getInstance()
{
    if (!mFont)
    {
        mFont = new Font();
    }
    return mFont;
}

void Font::init()
{
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    
    if (FT_New_Face(ft, "hanyi.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    
    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);
    
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    
    //gennarate a 4 * 1024 * 1024 texture to cache font
    glGenTextures(1, &mFontTextureCache);
    glBindTexture(GL_TEXTURE_2D, mFontTextureCache);
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 GL_RED,
                 TEXTURE_WIDTH,
                 TEXTURE_HEIGHT,
                 0,
                 GL_RED,
                 GL_UNSIGNED_BYTE,
                 NULL
                 );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    mCellInfos = new char[(TEXTURE_WIDTH / CHARACTER_CELL_SIZE)
                               * (TEXTURE_HEIGHT / CHARACTER_CELL_SIZE)];
    
    memset((char*)mCellInfos, 0, sizeof(char) * (TEXTURE_WIDTH / CHARACTER_CELL_SIZE)
           * (TEXTURE_HEIGHT / CHARACTER_CELL_SIZE));
    
    
    
    // Destroy FreeType once we're finished
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);
}

void Font::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    //Shader shader("text.vs", "text.frag");
    //shader.Use();
    // Activate corresponding render state
    //glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);

    int len = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c+=len)
    {
        FontInfo fontInfo;
        int result = 0;
        if ((*c & 0x80) == 0x0)
        {
            len = 1;
            result = *c;
        }
        else if ((*c & 0xE0) == 0xB0)
        {
            len = 2;
        }
        else if ((*c & 0xF0) == 0xE0)
        {
            len = 3;
            int m = (0x0F & *c);
            int n = (0x3F & *(c + 1));
            int k = (0x3F & *(c + 2));
            
            result = m << 12 | n << 6 | k;
        }

        Character ch = getCharacter(result);
        
        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        
        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,
                ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO },
            { xpos,     ypos,
                ch.cellPosition.col * CELL_RADIO, (float)ch.Size.y / TEXTURE_WIDTH + ch.cellPosition.row * CELL_RADIO },
            { xpos + w, ypos,
                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, (float)ch.Size.y / TEXTURE_WIDTH + ch.cellPosition.row * CELL_RADIO },
            
            { xpos,     ypos + h,   ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO },
            { xpos + w, ypos,
                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, (float)ch.Size.y / TEXTURE_WIDTH + ch.cellPosition.row * CELL_RADIO },
            { xpos + w, ypos + h,
                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO }        };
        
        float temp = ch.cellPosition.row * CELL_RADIO;
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,
//                ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO },
//            { xpos,     ypos,
//                ch.cellPosition.col * CELL_RADIO, (float)ch.Size.x / TEXTURE_WIDTH + (ch.cellPosition.row + 1) * CELL_RADIO },
//            { xpos + w, ypos,
//                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, (float)ch.Size.x / TEXTURE_WIDTH + (ch.cellPosition.row + 1) * CELL_RADIO },
//            
//            { xpos,     ypos + h,   ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO },
//            { xpos + w, ypos,
//                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, (float)ch.Size.x / TEXTURE_WIDTH + (ch.cellPosition.row + 1)* CELL_RADIO },
//            { xpos + w, ypos + h,
//                (float)ch.Size.x / TEXTURE_WIDTH + ch.cellPosition.col * CELL_RADIO, ch.cellPosition.row * CELL_RADIO }
//        };
        
//        GLfloat vertices[6][4] = {
//            { 0,     800,
//                0, 0},
//            { 0,     0,
//                0, 0.1 },
//            { 600, 0,
//                0.1, 0.1 },
//            
//            { 0,     800,   0,0 },
//            { 600, 0,
//                0.1,0.1},
//            { 600, 800,
//                0.1,0 }
//        };
//        GLfloat vertices[6][4] = {
//            { xpos, ypos + h, 0.0, 0.0 },
//            { xpos, ypos, 0.0, 0.1 },
//            { xpos + w, ypos, 0.1, 0.1 },
//            
//            { xpos, ypos + h, 0.0, 0.0 },
//            { xpos + w, ypos, 0.1, 0.1 },
//            { xpos + w, ypos + h, 0.1, 0.0 }
//        };
        memcpy(fontInfo.verteies, vertices, sizeof(GLfloat) * 6 * 4);
        fontInfo.textureID = ch.TextureID;
        
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        
        
        submit(fontInfo);
    }
}

Character Font::getCharacter(GLuint index)
{
    auto ch = mCharacters.find(index);
    if (ch != mCharacters.end()) {
        return ch->second;
    }
    
    // Load character glyph
    if (FT_Load_Char(face, index, FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    }
    CellPosition pos = getUnUsedCellPosition();
    
    glBindTexture(GL_TEXTURE_2D, mFontTextureCache);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    pos.col * CHARACTER_CELL_SIZE,
                    pos.row * CHARACTER_CELL_SIZE,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    GL_RED, GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer);
    
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
    Character character = {
        mFontTextureCache,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint)face->glyph->advance.x,
        pos
    };
    mCharacters.insert(std::pair<GLuint, Character>(index, character));
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return character;
}

void Font::submit(const FontInfo &fontInfo)
{
    Renderer::getInstance()->submit(fontInfo);
}

CellPosition Font::getUnUsedCellPosition()
{
    for (int i = 0; i < WIDTH_SIZE; ++i) {
        if (mCellInfos[mRowIndex * WIDTH_SIZE + i] == 0) {
            mCellInfos[mRowIndex * WIDTH_SIZE + i] = 1;
            
            CellPosition cellPosition = CellPosition(mRowIndex, i);
            if (mRowIndex == 63)
            {
                mRowIndex = 0;
            }
            else
            {
                mRowIndex++;
            }
            return cellPosition;
        }
    }
    return CellPosition(0, 0);
}

std::map<GLuint, Character> Font::getCharacters()
{
    return mCharacters;
}
