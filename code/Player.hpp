//
//  Player.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/21.
//

#ifndef Player_hpp
#define Player_hpp

#include <glm/glm.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <glm/gtc/matrix_transform.hpp>
#include <assert.h>
#include <stdio.h>
#include "Camera.hpp"
#include "Shader.hpp"
#include "DrawText.hpp"
#include <fbxsdk.h>


struct BoneVertex
{
    float r, g, b, a;
    float x, y, z;
    float weights[2];
    short matrixIndices[2];
    short numBones;
};

class Player{
public:
    
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 target;
    glm::vec3 WorldUp;
    float Pitch = 0;
    float Yaw  = 0;
    float SenseX=0.001f;
    float SenseY=0.001f;
    float speedZ = 0;
    float speedX = 0;
    float speedY = 0;
    float Health = 0;
    const float MaxHealth = 5;
    int pickNumber = 0;
    int modelNumber = 0;
    GLuint Body;
    GLuint Head;
  // Health
    Camera camera;
    Player(glm::vec3 position, glm::vec3 target,glm::vec3 worldup,Camera cam);
    ~Player();
    glm::mat4 GetPlayerViewMatrix();
    void ProcessMouseMovement(float deltaX, float deltaY);
    void UpdatePlayerPos();
    void Draw(int judge);
    void Wrong();
    void Tip(int i);
    void GetPosition(glm::vec3 Pos);
private:
    void UpdataPlayerVectors();
};
#endif /* Player_hpp */
