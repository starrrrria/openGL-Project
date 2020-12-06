//
//  DrawText.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/23.
//

#ifndef DrawText_hpp
#define DrawText_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "Shader.hpp"

struct Character {
    unsigned int     TextureID;  // 字形纹理的ID
    glm::ivec2 Size;       // 字形大小
    glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
    unsigned int     Advance;    // 原点距下一个字形原点的距离
    wchar_t data;//宽字符
    GLuint texture;//该字符贴图
    int left,top,width,height,bmp_width,bmp_rows;//贴图上的文字信息
};

class DrawText{
public:
    DrawText();
    ~DrawText();
    void LoadASCll();
    void getCharacter(char c);
    unsigned int VAO,VBO,EBO;
    void RenderText(Shader * s, std::string text, GLfloat x, GLfloat y, GLfloat scale,  glm::vec3 color);
    void setupText();
    void LoadChar();
    std::map<GLchar, Character> Characters;
};
#endif /* DrawText_hpp */
