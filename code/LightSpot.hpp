//
//  LightSpot.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/18.
//

#ifndef LightSpot_hpp
#define LightSpot_hpp
#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include <stdio.h>

class LightSpot{
public:
    LightSpot(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f));
    ~LightSpot();
    void UpdateDirection();
    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 direction = glm::vec3(0,0,1.0f);
    glm::vec3 color;
    
    float constant;
    float linear;
    float quadratic;
    
    float cosPhyInner = 0.9f;
    float cosPhyOutter = 0.85f;
};
#endif /* LightSpot_hpp */
