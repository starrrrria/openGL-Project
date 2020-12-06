//
//  LightDirectional.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/17.
//

#ifndef LightDirectional_hpp
#define LightDirectional_hpp
#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

class LightDirectional{
public:
    LightDirectional(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f));
    ~LightDirectional();
    void UpdateDirection();
    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 direction = glm::vec3(0,0,1.0f);
    glm::vec3 color;
    
};
#endif /* LightDirectional_hpp */
