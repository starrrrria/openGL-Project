//
//  PickTexture.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/28.
//

#ifndef PickTexture_hpp
#define PickTexture_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h> //目录下的档案
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdio.h>

class PickingTexture
{
public:
    PickingTexture();
    ~PickingTexture();
    void Init(unsigned int WindowWidth, unsigned int WindowHeight);
    void EnableWriting();
    void DisableWriting();
    struct PixelInfo {
        unsigned int ObjectID;
        unsigned int DrawID;
        unsigned int PrimID;
        PixelInfo()     {
            ObjectID = 0;
            DrawID = 0;
            PrimID = 0;
        }
    };
    PixelInfo ReadPixel(unsigned int x, unsigned int y);
private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;
};
#endif /* PickTexture_hpp */
