//
//  LightPoint.cpp
//  triangle
//
//  Created by 补锌 on 2020/11/18.
//

#include "LightPoint.hpp"

LightPoint::LightPoint(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color):
    position(_position),
    angles(_angles),
    color(_color)
{
    constant = 1.0f;
    linear = 0.3f;//衰减量
    quadratic = 0.032f;
}
LightPoint::~LightPoint(){
    
}
