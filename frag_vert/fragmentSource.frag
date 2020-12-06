#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;//u v坐标

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct LightPoint{
    float constant;
    float linear;//一次项系数
    float quadratic;//二次项
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};

struct LightSpot{
    float constant;
    float linear;//一次项系数
    float quadratic;
    float cosPhyInner;
    float cosPhyOutter;
    vec3 pos;
    vec3 color;
    vec3 dirToLight;
};

struct LightDirectional{
    vec3 pos;
    vec3 color;
    vec3 dirToLight; //从片源指向光的方向
};
uniform Material material;
uniform LightDirectional lightD;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;
uniform sampler2D shadowMap;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
float CalcShadowFactor(vec3 dirToCamera)
{
    vec2 UVCoords;
    UVCoords.x = 0.5 * dirToCamera.x + 0.5;
    UVCoords.y = 0.5 * dirToCamera.y + 0.5;
    float z = 0.5 * dirToCamera.z + 0.5;
    float Depth = texture(shadowMap, UVCoords).x;
    if (Depth < z + 0.00001)
        return 0.5;
    else
        return 1.0;
}
vec3 CalclightDirectional(LightDirectional light,vec3 uNormal, vec3 dirToCamera){
    //diffuse max(dot(L,N),0)
    float diffIntensity = max(dot(light.dirToLight,uNormal),0);//set min value
    vec3 diffColor = texture(material.diffuse, TexCoord).rgb * diffIntensity * light.color;
    //specular pow(max(dot(R,Cam),0),shininess)
    vec3 R = normalize(reflect(-light.dirToLight,uNormal));
    float specIntensity = pow(max(dot(R,dirToCamera),0),material.shininess);
    vec3 specColor = texture(material.specular,TexCoord).rgb * specIntensity * light.color;//uv坐标TexCoord
    vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;
    
    vec3 result = ambient + diffColor+ specColor;
    return result;
}
vec3 CalcLightPoint(LightPoint light,vec3 uNormal, vec3 dirToCamera){
    //attenuation
    float ShadowFactor = CalcShadowFactor(dirToCamera);
    float dist = length(light.pos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    //diffuse max(dot(L,N),0)
    vec3 lightDir = normalize(light.pos - FragPos); //vector pointing to the light,from //fragment pos
    float diffIntensity = max(dot(lightDir,uNormal),0)* attenuation;
    vec3 diffColor = texture(material.diffuse, TexCoord).rgb * diffIntensity * light.color;
    //specular pow(max(dot(R,Cam),0),shininess)
    vec3 R = normalize(reflect(-lightDir,uNormal));//光源指向片源
    float specIntensity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation;
    vec3 specColor = texture(material.specular,TexCoord).rgb * specIntensity * light.color;//uv坐标TexCoord
    
    vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;
    
    vec3 result = ambient + ShadowFactor*(diffColor+ specColor);
    return result;
}
vec3 CalcLightSpot(LightSpot light,vec3 uNormal, vec3 dirToCamera){
    //attenuation
    float dist = length(light.pos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    vec3 lightDir = normalize(light.pos - FragPos); //vector pointing to the light,from //fragment pos
    float cosTheta = dot(-lightDir, -1 * light.dirToLight);
    float spotRatio;
    
    if (cosTheta > light.cosPhyInner) {
        //inside
        spotRatio = 1.0f;
    }
    else if(cosTheta > light.cosPhyOutter){
        //middle
        //spotRatio = 0.5f;
        spotRatio =1.0f -( cosTheta - light.cosPhyInner) / (light.cosPhyOutter - light.cosPhyInner);
    }
    else{
        //outside
        spotRatio = 0;
    }
    //diffuse max(dot(L,N),0)
    
    float diffIntensity = max(dot(lightDir,uNormal),0)* spotRatio;
    vec3 diffColor = texture(material.diffuse, TexCoord).rgb * diffIntensity * light.color;
    //specular pow(max(dot(R,Cam),0),shininess)
    vec3 R = normalize(reflect(-lightDir,uNormal));//光源指向片源
    float specIntensity = pow(max(dot(R,dirToCamera),0),material.shininess) * spotRatio;
    vec3 specColor = texture(material.specular,TexCoord).rgb * specIntensity * light.color;//uv坐标TexCoord
    
    vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;
    
    vec3 result = ambient + diffColor+ specColor;
    return result;
}
void main(){
    
//    vec3 reflectVec = reflect(-lightDir,Normal);
//    vec3 cameraVec = normalize(cameraPos - FragPos);
//
    vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor; //决定最深处的颜色
    vec3 finalResult = vec3(0,0,0);
    vec3 uNormal = normalize(Normal);
    vec3 dirToCamera = normalize(cameraPos - FragPos);

    finalResult += CalclightDirectional(lightD,uNormal,dirToCamera);
    finalResult += CalcLightPoint(lightP0,uNormal,dirToCamera);
    finalResult += CalcLightPoint(lightP1,uNormal,dirToCamera);
    finalResult += CalcLightPoint(lightP2,uNormal,dirToCamera);
    finalResult += CalcLightPoint(lightP3,uNormal,dirToCamera);
    finalResult += CalcLightSpot(lightS,uNormal,dirToCamera);
    FragColor = vec4(finalResult, 1.0);
    //FragColor = vec4(1.0f,1.0f,1.0f,1.0f);

}
