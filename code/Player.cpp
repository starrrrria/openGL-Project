//
//  Player.cpp
//  triangle
//
//  Created by 补锌 on 2020/11/21.
//
#include <GLUT/glut.h>
#include "Player.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include "Camera.hpp"
#include "Shader.hpp"
#include "DrawText.hpp"
#include "Material.hpp"
#include <iostream>
#define GL_SILENCE_DEPRECATION
Player::Player(glm::vec3 position, glm::vec3 target,glm::vec3 worldup,Camera cam):
camera(cam)
{
    Position = position;
    WorldUp  = worldup;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right)); //叉乘
    std::cout << "Press W,S,A,D move, F pick up/put down things, V change first/third person camera, mouse rotate angle of view. " << std::endl;
}

Player::~Player() {
}
glm::mat4 Player::GetPlayerViewMatrix(){
    return  glm::lookAt(Position, Position+Forward, WorldUp);
}
void Player::UpdataPlayerVectors(){
    Forward = glm::normalize(target - Position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Right, Forward));
}

void Player::ProcessMouseMovement(float deltaX, float deltaY){
    
    Pitch -= deltaY * SenseX;
    Yaw -= deltaX * SenseY;
    target.x = glm::cos(Pitch)*glm::sin(Yaw);
    target.z = glm::cos(Pitch)*glm::cos(Yaw);
    UpdataPlayerVectors();
}
void Player::GetPosition(glm::vec3 Pos){
    Position = Pos;
    //std::cout << "player" << Position.x << Position.z << std::endl;
}
void Player::UpdatePlayerPos(){
    
    Position.x = -camera.firstPosition.x;
    Position.y = camera.firstPosition.y;
    Position.z = -camera.firstPosition.z;
    //std::cout << Position.x << Position.z << std::endl;
}
void Player::Wrong(){
    std::cout << "You can't pick this thing" << std::endl;
}
void Player::Tip(int i){
    if (i == 0) {
        std::cout << "This is recycle trash bin" << std::endl;
    }
    else if(i == 1){
        std::cout << "This is other trash bin" << std::endl;
    }
    else if (i == 2){
        std::cout << "This is harmful trash bin" << std::endl;
    }
    else{
        std::cout << "This is kitchen trash bin" << std::endl;
    }
}
void Player::Draw(int judge) {
//    DrawText draw;
//    draw.RenderText(s, std::to_string(HealthBar.Health), 540.0f, 570.0f, fontHeight, glm::vec3(0.3, 0.7f, 0.9f));
    if (judge == 1) {
        Health += 1;
        std::cout << "Your point is:" << Health << std::endl;
    }
    else if(judge == 0){
        std::cout << "Your point is:" << Health << std::endl;
    }
    if (Health == 5) {
        std::cout << "You win the game" << std::endl;
    }
}


