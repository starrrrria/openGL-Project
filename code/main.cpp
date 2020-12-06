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
#include <ft2build.h>
#include <freetype/freetype.h>
#include <assert.h>
#include <AntTweakBar.h>
#include "stdio.h"

#include "Shader.hpp" //隶属于本项目的档案
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.hpp"
#include "LightDirectional.hpp"
#include "LightPoint.hpp"
#include "LightSpot.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Player.hpp"
#include "DrawText.hpp"
#include "PickTexture.hpp"

using namespace::glm;

//Model Data
float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
float PlayerVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
vec3 cubePositions[] = {
    vec3(20.0f,-2.0f,18.5f),//right wall
    vec3(-20.0f,-2.0f,18.5f), //left wall
    vec3(20.0f,-2.0f,18.5f),//behind wall
    vec3(20.0f,-2.0f,-22.0f)//
};
vec3 wingPositions[] = {
    vec3(0.6f,6.0f,-1.0f),
    vec3(-1.0f,6.0f,-1.0f)
};

float wingAngle[] = {
    -120.0f,300.0f
};
vec3 garbagePositions[] = {
    vec3(-2.0,-2.0f,-9.0f), //book
    vec3(2.0f,-1.0f,-3.0f), //can
    vec3(5.0f,-0.8f,0.0f), //rose
    vec3(-1.0f,-1.25f,4.0f), //fish
    vec3(-8.0f,-1.0f,-4.0f),  //cup
    vec3(-9.0f,-1.9f,3.0f), //Pill
};
vec3 binPositions[] = {
    vec3(-5.0f,-1.5f,3.0f),
    vec3(-5.0f,-1.5f,0.0f),
    vec3(-5.0f,-1.5f,-3.0f),
    vec3(-5.0f,-1.5f,-6.0f)
};
vec3 binAmbient[] = {
    vec3(0.1f,0.1f,0.1f), //blue recycle
    vec3(0.0f,0.0f,0.0f), //black other
    vec3(0.1f,0.0f,0.0f), //red harmful
    vec3(0.0f,0.1f,0.0f) //green kitchen
};
float roteAngle[] = {
    0,0,90.0f,90.0f
};
//Camera Declare
//Instantiate Camera class
//Camera camera(vec3(0,0,3.0f),vec3(0,0,0),vec3(0,1.0f,0));
Camera camera(vec3(0,0,3.0f),radians(15.0f),radians(180.0f),vec3(0,1.0f,0));
Player players(vec3(0,-3.0f,3.0f),vec3(0,0,0),vec3(0,1.0f,0),camera);

//Light Dclare
LightDirectional light (vec3(-0.0f,3.0f,0.0f),vec3(radians(0.0f),0,0),vec3(1.0f,1.0f,1.0f));
LightPoint lightP0 (vec3(0.0f,1.0f,0.0f),vec3(radians(45.0f),0,0),vec3(3.0f,0.0f,0.0f));
LightPoint lightP1 (vec3(1.0f,0.0f,0.0f),vec3(radians(45.0f),0,0),vec3(0.0f,2.0f,0.0f));
LightPoint lightP2(vec3(0.0f,0.0f,1.0f),vec3(radians(45.0f),0,0),vec3(0.0f,0.0f,3.0f));
LightPoint lightP3 (vec3(1.0f,1.0f,1.0f),vec3(radians(45.0f),0,0),vec3(2.0f,2.0f,2.0f));
LightSpot lightS (vec3(0.0f,20.0f,0.0f),vec3(radians(90.0f),0,0),vec3(1.0f,1.0f,1.0f));


//Input Declare
float lastX;
float lastY;
float Angle = 0;
void update(){
    float lastTime = 0;
    float currTime = (float)glfwGetTime();
    float  delta = (currTime - lastTime) * 0.001f;
    if (delta > 0.03f){
        delta = 0.03f;
        lastTime = currTime;
        Angle += 0.2f;
    }
    
}
bool firstMouse = true;

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.speedZ = 1.0f;
        players.speedZ = 1.0f;
        
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.speedZ = -1.0f;
        players.speedZ = -1.0f;
    }
    else{
        camera.speedZ = 0;
        players.speedZ = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.speedX = 1.0f;
        players.speedX = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.speedX = -1.0f;
        players.speedX = -1.0f;
    }
    else{
        camera.speedX = 0;
        players.speedX = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.speedY = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.speedY = 1.0f;
    }
    else{
        camera.speedY = 0;
        players.speedY = 0;
    }
};

static void key_callback(GLFWwindow *window,int key, int scancode, int action, int mods){
    
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) { //change first and third camera
        camera.changeNumber += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) { //change first and third camera
        if ((players.pickNumber % 2) == 0) {
            if(camera.firstPosition.x <= (garbagePositions[0].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[0].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[0].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[0].z - 1.0f)){
                players.modelNumber = 1;
            }
            else if(camera.firstPosition.x <= (garbagePositions[1].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[1].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[1].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[1].z - 1.0f)){
                players.modelNumber = 2;
            }
            else if(camera.firstPosition.x <= (garbagePositions[2].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[2].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[2].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[2].z - 1.0f)){
                players.modelNumber = 3;
            }
            else if(camera.firstPosition.x <= (garbagePositions[3].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[3].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[3].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[3].z - 1.0f)){
                players.modelNumber = 4;
            }
            else if(camera.firstPosition.x <= (garbagePositions[4].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[4].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[4].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[4].z - 1.0f)){
                players.modelNumber = 5;
            }
            else if(camera.firstPosition.x <= (garbagePositions[5].x + 1.0f) && camera.firstPosition.x >= (garbagePositions[5].x - 1.0f) && camera.firstPosition.z <= (garbagePositions[5].z + 1.0f) && camera.firstPosition.z >= (garbagePositions[5].z - 1.0f)){
                players.modelNumber = 6;
            }
            players.pickNumber += 1;
        }
        else{
            if (players.modelNumber == 0) {
                players.Wrong();
            }
            else{
                players.pickNumber += 1;
            }
        }
    }
}
void mouse_callback(GLFWwindow* window, double xPos,double yPos){
    if (firstMouse == true) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX,deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement(deltaX, deltaY);
    players.ProcessMouseMovement(deltaX, deltaY);
}

unsigned int LoadImageToGPU(const char* filename,GLint internalFormat, GLenum format,int textureSlot){
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer); //产生buffer
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);
    
    int width,height,nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename,&width,&height,&nrChannel,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } //第几登记mipmap,不给边缘
    else{
        printf("load image failed.");
    }
    stbi_image_free(data);
    return TexBuffer;
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc,char* argv[])
{
    std::string exePath = argv[0];
    //std::cout << exePath.substr(0,exePath.find_last_of('/'))+ '/Structure/Structure/Wall-Window.obj' << std::endl;
    //Open window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //终止
        return -1;
    }
    glfwMakeContextCurrent(window); //绑定使用
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW fault");
        glfwTerminate();
        return -1;
    }
    
    // Initialize the GUI
    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(1024, 768);
    TwBar * GUI = TwNewBar("Picking");
    TwSetParam(GUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
    std::string message;
    TwAddVarRW(GUI, "Last picked object", TW_TYPE_STDSTRING, &message, NULL);
    
    glViewport(0, 0, 800, 600); //设置窗口大小起始坐标终止坐标
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    //Init Shader Program
//    Shader* TextShader = new Shader("/Users/buxin/Desktop/triangle/CharacterVertex.vert","/Users/buxin/Desktop/triangle/CharacterFragment.frag");
    Shader* testShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* TableShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* FloorShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* WallShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* TrashbinShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* PlayerShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* BookShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* CanShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* RoseShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* fishShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* CupShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* PillShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* cube1Shader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
    Shader* WingShader = new Shader("/Users/buxin/Desktop/triangle/vertexSource.vert","/Users/buxin/Desktop/triangle/fragmentSource.frag");
//    Shader* PickShader = new Shader("/Users/buxin/Desktop/triangle/PickVertex.vert","/Users/buxin/Desktop/triangle/PickFragment.frag");
    
    //Init Material
    Material* myMaterial = new Material(testShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/backpack/diffuse.jpg", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
                                        LoadImageToGPU("/Users/buxin/Downloads/backpack/specular.jpg", GL_RGBA, GL_RGBA, Shader::SPECULAR),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* TableMaterial = new Material(TableShader,
                                        LoadImageToGPU("/Users/buxin/Documents/computer graphic/Tables/Tables/TexturesCom_WoodFine0034_1_seamless_S.jpg", GL_RGBA, GL_RGBA, 3),
                                        LoadImageToGPU("/Users/buxin/Documents/computer graphic/Tables/Tables/TexturesCom_WoodFine0034_1_seamless_S.jpg", GL_RGBA, GL_RGBA, 4),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* WallMaterial = new Material(WallShader,
                                        LoadImageToGPU("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Window/TexturesCom_MarbleWhite0040_1_seamless_S.jpg", GL_RGBA, GL_RGBA, 5),
                                        LoadImageToGPU("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Window/TexturesCom_WoodFine0035_1_seamless_S.jpg ", GL_RGBA, GL_RGBA,6),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* TrashbinMaterial = new Material(TrashbinShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/TrashbinBlue_basecolor.png", GL_RGBA, GL_RGBA, 7),
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_roughness.png", GL_RGBA, GL_RGBA,8),
                                        //LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_normal.png", GL_RGBA, GL_RGBA,Shader::NORMAL),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* TrashbinMaterial1 = new Material(TrashbinShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/TrashbinYellow_basecolor.png", GL_RGBA, GL_RGBA, 9),
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_roughness.png", GL_RGBA, GL_RGBA,10),
                                        //LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_normal.png", GL_RGBA, GL_RGBA,Shader::NORMAL),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* TrashbinMaterial2 = new Material(TrashbinShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/TrashbinRed_basecolor.png", GL_RGBA, GL_RGBA, 11),
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_roughness.png", GL_RGBA, GL_RGBA,12),
                                        //LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_normal.png", GL_RGBA, GL_RGBA,Shader::NORMAL),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* TrashbinMaterial3 = new Material(TrashbinShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/TrashbinGreen_basecolor.png", GL_RGBA, GL_RGBA, 13),
                                        LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_roughness.png", GL_RGBA, GL_RGBA,14),
                                        //LoadImageToGPU("/Users/buxin/Downloads/Trashbin/Trashbin_normal.png", GL_RGBA, GL_RGBA,Shader::NORMAL),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* PlayerMaterial = new Material(PlayerShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Stacy/Stacy_dif.tga", GL_RGBA, GL_RGBA, 15),
                                        LoadImageToGPU("/Users/buxin/Downloads/Stacy/Stacy_spec.tga", GL_RGBA, GL_RGBA, 16),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* BookMaterial = new Material(BookShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/book/1984-book_A.jpg", GL_RGBA, GL_RGBA, 17),
                                        LoadImageToGPU("/Users/buxin/Downloads/book/1984-book_C.jpg", GL_RGBA, GL_RGBA, 18),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* CanMaterial = new Material(CanShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/Can/KuimiBeerCan_color.png", GL_RGBA, GL_RGBA, 19),
                                        LoadImageToGPU("/Users/buxin/Downloads/Can/KuimiBeerCan_roughness.png", GL_RGBA, GL_RGBA, 20),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* RoseMaterial = new Material(RoseShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/rose/wildtextures-leather-Campo-rose.jpg", GL_RGBA, GL_RGBA, 21),
                                        LoadImageToGPU("/Users/buxin/Downloads/rose/grass_texture225.jpg", GL_RGBA, GL_RGBA, 22),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* fishMaterial = new Material(fishShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/fish/fish_texture.png", GL_RGBA, GL_RGBA, 23),
                                        LoadImageToGPU("/Users/buxin/Downloads/fish/fish_texture.png", GL_RGBA, GL_RGBA, 24),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* CupMaterial = new Material(CupShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/coffee-cup/coffee_cup.jpg", GL_RGBA, GL_RGBA, 25),
                                        LoadImageToGPU("/Users/buxin/Downloads/coffee-cup/cap _roughness.jpeg", GL_RGBA, GL_RGBA, 26),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* PillMaterial = new Material(PillShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/pill-bottle/Pill-Bottle-Label-PSD-Template.jpg", GL_RGBA, GL_RGBA, 27),
                                        LoadImageToGPU("/Users/buxin/Downloads/pill-bottle/Pill-Bottle-Label-PSD-Template.jpg", GL_RGBA, GL_RGBA, 28),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* cube1Material = new Material(cube1Shader,
                                        LoadImageToGPU("/Users/buxin/Downloads/pill-bottle/Pill-Bottle-Label-PSD-Template.jpg", GL_RGBA, GL_RGBA, 27),
                                        LoadImageToGPU("/Users/buxin/Downloads/pill-bottle/Pill-Bottle-Label-PSD-Template.jpg", GL_RGBA, GL_RGBA, 28),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Material* WingMaterial = new Material(WingShader,
                                        LoadImageToGPU("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Window/TexturesCom_MarbleWhite0040_1_seamless_S.jpg", GL_RGBA, GL_RGBA, 29),
                                        LoadImageToGPU("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Window/TexturesCom_WoodFine0035_1_seamless_S.jpg ", GL_RGBA, GL_RGBA,30),
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    //Init and load models to VAO ,VBO
    Mesh cube1(vertices);
    Model model("/Users/buxin/Downloads/backpack/backpack.obj");
    Model TableModel("/Users/buxin/Documents/computer graphic/Tables/Tables/Coffee Table.obj");
    Model FloorModel("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Segment.obj");
    Model WallModel("/Users/buxin/Desktop/triangle/triangle/Structure/Structure/Wall-Segment.obj");
    Model TrashbinModel("/Users/buxin/Downloads/Trashbin/Trashbin.obj");
    Model PlayerModel("/Users/buxin/Downloads/Stacy/Stacy.obj");
    Model WingModel("/Users/buxin/Downloads/Eagle_Wing/Eagle_Wing_v1.obj");
    Model BookModel("/Users/buxin/Downloads/book/1984_book.obj",1,"book");
    Model CanModel("/Users/buxin/Downloads/Can/KuimiBeerCan.obj",2,"can");
    Model RoseModel("/Users/buxin/Downloads/rose/rose.obj",3,"rose");
    Model fishModel("/Users/buxin/Downloads/fish/fish.obj",4,"fish");
    Model CupModel("/Users/buxin/Downloads/coffee-cup/coffee_cup.obj",5,"cup");
    Model PillModel("/Users/buxin/Downloads/pill-bottle/Pill_Bottle.obj",6,"pill");
    
    //Prepare MVP matrices
    //calculate our transformation matrix
    mat4 modelMat = mat4(1.0f);
    mat4 TableModelMat = mat4(1.0f);
    mat4 FloorModelMat = mat4(1.0f);
    mat4 WallModelMat = mat4(1.0f);
    mat4 PlayerModelMat = mat4(1.0f);
    mat4 WingModelMat = mat4(1.0f);
    mat4 TrashbinModelMat = mat4(1.0f);
    mat4 BookModelMat = mat4(1.0f);
    mat4 CanModelMat = mat4(1.0f);
    mat4 RoseModelMat = mat4(1.0f);
    mat4 fishModelMat = mat4(1.0f);
    mat4 CupModelMat = mat4(1.0f);
    mat4 PillModelMat = mat4(1.0f);
    mat4 cube1ModelMat = mat4(1.0f);
    mat4 viewMat = mat4(1.0f);
    mat4 projMat = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    
    
    while (!glfwWindowShouldClose(window)) {
        //Process input
        processInput(window); //下一帧输入
        glfwSetKeyCallback(window, key_callback);
        //Clear screen
        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if((camera.changeNumber%2) == 1){
            viewMat = camera.GetthirdViewMatrix();
        }
        else{
            viewMat = camera.GetfirstViewMatrix();
        }
        
        //text
//        TextShader->use();
//        glUniformMatrix4fv(glGetUniformLocation(TextShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projText));
        
        
        //Set Model matrix
        modelMat = translate(mat4(1.0f), vec3(0,-1.0f,-5.0f));
        
            //Set View and Projection Matrices here if you want
        modelMat = scale(modelMat, vec3(0.5f,0.5f,0.5f));
            //Set Material -> Shader Program
        testShader -> use();
            //Set material -> Textures
        
        glUniformMatrix4fv(glGetUniformLocation(testShader->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(testShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(testShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(testShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(testShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
        glUniform1i(glGetUniformLocation(testShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(testShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(testShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(testShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
            
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP0.pos"),lightP0.position.x,lightP0.position.y,lightP0.position.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP0.color"),lightP0.color.x,lightP0.color.y,lightP0.color.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP0.direction"),lightP0.direction.x,lightP0.direction.y,lightP0.direction.z);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP0.constant"),lightP0.constant);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP0.linear"),lightP0.linear);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP0.quadratic"),lightP0.quadratic);
//
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP1.pos"),lightP1.position.x,lightP1.position.y,lightP1.position.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP1.color"),lightP1.color.x,lightP1.color.y,lightP1.color.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP1.direction"),lightP1.direction.x,lightP1.direction.y,lightP1.direction.z);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP1.constant"),lightP1.constant);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP1.linear"),lightP1.linear);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP1.quadratic"),lightP1.quadratic);
//
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP2.pos"),lightP2.position.x,lightP2.position.y,lightP2.position.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP2.color"),lightP2.color.x,lightP2.color.y,lightP2.color.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP2.direction"),lightP2.direction.x,lightP2.direction.y,lightP2.direction.z);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP2.constant"),lightP2.constant);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP2.linear"),lightP2.linear);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP2.quadratic"),lightP2.quadratic);
//
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP3.pos"),lightP3.position.x,lightP3.position.y,lightP3.position.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP3.color"),lightP3.color.x,lightP3.color.y,lightP3.color.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightP3.direction"),lightP3.direction.x,lightP3.direction.y,lightP3.direction.z);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP3.constant"),lightP3.constant);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP3.linear"),lightP3.linear);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightP3.quadratic"),lightP3.quadratic);
//
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightS.pos"),lightS.position.x,lightS.position.y,lightS.position.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightS.color"),lightS.color.x,lightS.color.y,lightS.color.z);
//        glUniform3f(glGetUniformLocation(testShader->ID,"lightS.direction"),lightS.direction.x,lightS.direction.y,lightS.direction.z);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightS.constant"),lightS.constant);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightS.linear"),lightS.linear);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightS.quadratic"),lightS.quadratic);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightS.cosPhyInner"),lightS.cosPhyInner);
//        glUniform1f(glGetUniformLocation(testShader->ID,"lightS.cosPhyOutter"),lightS.cosPhyOutter);
            
        glUniform3f(glGetUniformLocation(testShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
        myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
        myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
        myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
          
          //Set model
//            glBindVertexArray(VAO);
          //Drawcall
//            glDrawArrays(GL_TRIANGLES, 0, 36); //从0开始，画三个顶点
          //cube.Draw(myMaterial->shader);
        model.Draw(myMaterial->shader);

        //Table model
        
        TableModelMat = translate(mat4(1.0f), vec3(5.0f,-1.5f,0.0f));
        TableModelMat = rotate(TableModelMat, radians(90.0f),vec3(0.0f, 4.0f, 0.0f));
        TableModelMat = scale(TableModelMat, vec3(0.5f,0.5f,0.5f));
        TableShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(TableShader->ID,"modelMat"),1,GL_FALSE,value_ptr(TableModelMat));
        glUniformMatrix4fv(glGetUniformLocation(TableShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(TableShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(TableShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(TableShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
           
        glUniform3f(glGetUniformLocation(TableShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(TableShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(TableShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(TableShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(TableShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        TableMaterial->shader->SetUniform3f("material.ambient", TableMaterial->ambient);
        TableMaterial->shader->SetUniform1i("material.diffuse", 3);
        TableMaterial->shader->SetUniform1i("material.specular", 4);
        TableMaterial->shader->SetUniform1f("material.shininess", TableMaterial->shininess);
        TableModel.Draw(TableMaterial->shader);
        
        //Floor model
        
        FloorModelMat = translate(mat4(1.0f), vec3(20.0f,-2.0f,-0.0f));
        FloorModelMat = rotate(FloorModelMat, radians(90.0f),vec3(0.0f, 1.0f, 0.0f));
        FloorModelMat = scale(FloorModelMat, vec3(83.0f,0.0f,20.0f));
        FloorShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(FloorShader->ID,"modelMat"),1,GL_FALSE,value_ptr(FloorModelMat));
        glUniformMatrix4fv(glGetUniformLocation(FloorShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(FloorShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(FloorShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(FloorShader->ID,"ambientColor"),0.2f,0.2f,0.3f);//环境光
           
        glUniform3f(glGetUniformLocation(FloorShader->ID,"lightS.pos"),lightS.position.x,lightS.position.y,lightS.position.z);
        glUniform3f(glGetUniformLocation(FloorShader->ID,"lightS.color"),lightS.color.x,lightS.color.y,lightS.color.z);
        glUniform3f(glGetUniformLocation(FloorShader->ID,"lightS.direction"),lightS.direction.x,lightS.direction.y,lightS.direction.z);
        glUniform1f(glGetUniformLocation(FloorShader->ID,"lightS.constant"),lightS.constant);
        glUniform1f(glGetUniformLocation(FloorShader->ID,"lightS.linear"),lightS.linear);
        glUniform1f(glGetUniformLocation(FloorShader->ID,"lightS.quadratic"),lightS.quadratic);
        glUniform1f(glGetUniformLocation(FloorShader->ID,"lightS.cosPhyInner"),lightS.cosPhyInner);
        glUniform1f(glGetUniformLocation(FloorShader->ID,"lightS.cosPhyOutter"),lightS.cosPhyOutter);
        glUniform1i(glGetUniformLocation(FloorShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(FloorShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        WallMaterial->shader->SetUniform3f("material.ambient", WallMaterial->ambient);
        WallMaterial->shader->SetUniform1i("material.diffuse", 5);
        WallMaterial->shader->SetUniform1i("material.specular", 6);
        WallMaterial->shader->SetUniform1f("material.shininess", WallMaterial->shininess);
        FloorModel.Draw(WallMaterial->shader);
        
        //Wall model
        for(int i = 0; i <4; i++){
            
            WallModelMat = translate(mat4(1.0f), cubePositions[i]);
            WallModelMat = rotate(WallModelMat, radians(roteAngle[i]),vec3(0.0f, 1.0f, 0.0f));
            WallModelMat = scale(WallModelMat, vec3(1.0f,1.0f,20.0f));
            WallShader -> use();
            glUniformMatrix4fv(glGetUniformLocation(WallShader->ID,"modelMat"),1,GL_FALSE,value_ptr(WallModelMat));
            glUniformMatrix4fv(glGetUniformLocation(WallShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(WallShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
            glUniform3f(glGetUniformLocation(WallShader->ID,"objColor"),0.8f,0.3f,1.0f);
            glUniform3f(glGetUniformLocation(WallShader->ID,"ambientColor"),0.3f,0.3f,0.3f);//环境光
               
            glUniform3f(glGetUniformLocation(WallShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
            glUniform3f(glGetUniformLocation(WallShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
            glUniform3f(glGetUniformLocation(WallShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
            glUniform1i(glGetUniformLocation(WallShader->ID,"shadowMap"),0);
            glUniform3f(glGetUniformLocation(WallShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
            WallMaterial->shader->SetUniform3f("material.ambient", WallMaterial->ambient);
            WallMaterial->shader->SetUniform1i("material.diffuse", 5);
            WallMaterial->shader->SetUniform1i("material.specular", 6);
            WallMaterial->shader->SetUniform1f("material.shininess", WallMaterial->shininess);
            WallModel.Draw(WallMaterial->shader);
        }
        
        //Trashbin model
        for (int i = 0; i < 4; i++) {
            TrashbinModelMat = translate(mat4(1.0f), binPositions[i]);
            if (players.Position.x <= (-binPositions[i].x + 0.5f) && players.Position.x >= (-binPositions[i].x - 0.5f) && players.Position.z <= (-binPositions[i].z + 0.5f) && players.Position.z >= (-binPositions[i].z - 0.5f)) {
                players.Tip(i);
            }
            TrashbinShader -> use();
            glUniformMatrix4fv(glGetUniformLocation(TrashbinShader->ID,"modelMat"),1,GL_FALSE,value_ptr(TrashbinModelMat));
            glUniformMatrix4fv(glGetUniformLocation(TrashbinShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(TrashbinShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"objColor"),1.0f,1.0f,1.0f);
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"ambientColor"),binAmbient[i].x,binAmbient[i].y,binAmbient[i].z);//环境光
               
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
            glUniform1i(glGetUniformLocation(TrashbinShader->ID,"shadowMap"),0);
            glUniform3f(glGetUniformLocation(TrashbinShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
            if (i == 0) {
                TrashbinMaterial->shader->SetUniform3f("material.ambient", TrashbinMaterial->ambient);
                TrashbinMaterial->shader->SetUniform1i("material.diffuse", 7);
                TrashbinMaterial->shader->SetUniform1i("material.specular", 8);
                TrashbinMaterial->shader->SetUniform1f("material.shininess", TrashbinMaterial->shininess);
                TrashbinModel.Draw(TrashbinMaterial->shader);
            }
            else if (i == 1){
                TrashbinMaterial1->shader->SetUniform3f("material.ambient", TrashbinMaterial1->ambient);
                TrashbinMaterial1->shader->SetUniform1i("material.diffuse", 9);
                TrashbinMaterial1->shader->SetUniform1i("material.specular", 10);
                TrashbinMaterial1->shader->SetUniform1f("material.shininess", TrashbinMaterial1->shininess);
                TrashbinModel.Draw(TrashbinMaterial1->shader);
            }
            else if (i ==2){
                TrashbinMaterial2->shader->SetUniform3f("material.ambient", TrashbinMaterial2->ambient);
                TrashbinMaterial2->shader->SetUniform1i("material.diffuse", 11);
                TrashbinMaterial2->shader->SetUniform1i("material.specular", 12);
                TrashbinMaterial2->shader->SetUniform1f("material.shininess", TrashbinMaterial2->shininess);
                TrashbinModel.Draw(TrashbinMaterial2->shader);
            }
            else{
                TrashbinMaterial3->shader->SetUniform3f("material.ambient", TrashbinMaterial3->ambient);
                TrashbinMaterial3->shader->SetUniform1i("material.diffuse", 13);
                TrashbinMaterial3->shader->SetUniform1i("material.specular", 14);
                TrashbinMaterial3->shader->SetUniform1f("material.shininess", TrashbinMaterial3->shininess);
                TrashbinModel.Draw(TrashbinMaterial3->shader);
            }
        }
        
        //Player model
        PlayerModelMat = translate(mat4(1.0f), vec3(0.0f,-3.0f,0.0f));
        
        PlayerModelMat = rotate(PlayerModelMat, radians(180.0f), vec3(0,1.0f,0.0f));
        PlayerModelMat = translate(PlayerModelMat, vec3(-camera.firstPosition.x,camera.firstPosition.y,-camera.firstPosition.z));
//            PlayerModelMat = translate(PlayerModelMat, vec3(-camera.Position.x - (5*camera.Forward.x),camera.Position.y,-camera.Position.z-(5*camera.Forward.x)));
        if(camera.Forward.z <= 0){
        PlayerModelMat = rotate(PlayerModelMat, -1.0f*camera.Forward.x, vec3(0,1.0f,0));
        }
        else if(camera.Forward.z > 0){
            PlayerModelMat = rotate(PlayerModelMat, 1.0f*camera.Forward.x+ radians(180.0f), vec3(0,1.0f,0));
        }
        players.GetPosition(vec3(-camera.firstPosition.x,camera.firstPosition.y,-camera.firstPosition.z));
        PlayerModelMat = scale(PlayerModelMat, vec3(0.25f,0.25f,0.25f));
        mat4 gloabl1  = PlayerModelMat;
        PlayerShader -> use();
        
        glUniformMatrix4fv(glGetUniformLocation(PlayerShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl1));
        glUniformMatrix4fv(glGetUniformLocation(PlayerShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(PlayerShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
           
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(PlayerShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(PlayerShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        PlayerMaterial->shader->SetUniform3f("material.ambient", PlayerMaterial->ambient);
        PlayerMaterial->shader->SetUniform1i("material.diffuse", 15);
        PlayerMaterial->shader->SetUniform1i("material.specular", 16);
        PlayerMaterial->shader->SetUniform1f("material.shininess", PlayerMaterial->shininess);
        PlayerModel.Draw(PlayerMaterial->shader);
        
        //wing model
        for(int i = 0; i <2; i++){
            
            WingModelMat = translate(mat4(1.0f),wingPositions[i]);
            WingModelMat = rotate(WingModelMat, radians(wingAngle[i]),vec3(0.0f, 1.0f, 0.0f));
            WingModelMat = rotate(WingModelMat, radians(90.0f),vec3(0.0f, 0.0f, 1.0f));
            WingModelMat = rotate(WingModelMat, radians(90.0f),vec3(1.0f, 0.0f, 0.0f));
            WingModelMat = rotate(WingModelMat, radians(105.0f),vec3(0.0f, 1.0f, 0.0f));
            //WingModelMat = rotate(WingModelMat, radians((float)glfwGetTime()),vec3(0.0f, 8.0f, 0.0f));
            WingModelMat = scale(WingModelMat, vec3(1.0f,0.5f,1.0f));
            mat4 gloabl2  = gloabl1 * WingModelMat;
            WingShader -> use();
            glUniformMatrix4fv(glGetUniformLocation(WingShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl2));
            glUniformMatrix4fv(glGetUniformLocation(WingShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(WingShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
            glUniform3f(glGetUniformLocation(WingShader->ID,"objColor"),0.8f,0.3f,1.0f);
            glUniform3f(glGetUniformLocation(WingShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
               
            glUniform3f(glGetUniformLocation(WingShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
            glUniform3f(glGetUniformLocation(WingShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
            glUniform3f(glGetUniformLocation(WingShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
            glUniform1i(glGetUniformLocation(WingShader->ID,"shadowMap"),0);
            glUniform3f(glGetUniformLocation(WingShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
            WingMaterial->shader->SetUniform3f("material.ambient", WingMaterial->ambient);
            WingMaterial->shader->SetUniform1i("material.diffuse", 29);
            WingMaterial->shader->SetUniform1i("material.specular", 30);
            WingMaterial->shader->SetUniform1f("material.shininess", WingMaterial->shininess);
            WingModel.Draw(WingMaterial->shader);
        }
        //book model
        mat4 gloabl3 = mat4(1.0f);
        BookModelMat = translate(mat4(1.0f), garbagePositions[0]);
        BookModelMat = scale(BookModelMat, vec3(0.5f,0.5f,0.5f));
        if((players.pickNumber%2) == 1 && players.modelNumber == 1){
            gloabl3  = gloabl1 * BookModelMat;
            BookModel.PickState();
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 1){
            if (players.Position.x <= (-binPositions[0].x + 0.5f) && players.Position.x >= (-binPositions[0].x - 0.5f) && players.Position.z <= (-binPositions[0].z + 0.5f) && players.Position.z >= (-binPositions[0].z - 0.5f)) {
                int judge = 1;
                BookModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
                //gloabl3 = translate(mat4(1.0f), binPositions[0]);
            }
            else{
                int judge = 0;
                //gloabl3  = BookModelMat;
                BookModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (BookModel.pick == 0) {
                gloabl3  = BookModelMat;
            }
            else{
                gloabl3  = translate(mat4(1.0f), binPositions[0]);
                gloabl3 = scale(gloabl3, vec3(0.5f,0.5f,0.5f));
            }
        }
        
        BookShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(BookShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl3));
        glUniformMatrix4fv(glGetUniformLocation(BookShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(BookShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(BookShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(BookShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光

        glUniform3f(glGetUniformLocation(BookShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(BookShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(BookShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(BookShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(BookShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        BookMaterial->shader->SetUniform3f("material.ambient", BookMaterial->ambient);
        BookMaterial->shader->SetUniform1i("material.diffuse", 17);
        BookMaterial->shader->SetUniform1i("material.specular", 18);
        BookMaterial->shader->SetUniform1f("material.shininess", BookMaterial->shininess);
        BookModel.Draw(BookMaterial->shader);


        //Can model
        mat4 gloabl4 = mat4(1.0f);
        CanModelMat = translate(mat4(1.0f), garbagePositions[1]);
        CanModelMat = scale(CanModelMat, vec3(1.5f,1.5f,1.5f));
        if((players.pickNumber%2) == 1 && players.modelNumber == 2){
            gloabl4  = gloabl1 * CanModelMat;
            //CanModelMat = translate(CanModelMat, vec3(garbagePositions[1].x,100.0f,garbagePositions[1].z));
            //CanModel.GetPosition(vec3(garbagePositions[1].x,100.0f,garbagePositions[1].z));
            CanModel.PickState();
            //CanModelMat = translate(CanModelMat, vec3(-camera.firstPosition.x,camera.firstPosition.y,-camera.firstPosition.z));
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 2){
            if (players.Position.x <= (-binPositions[0].x + 1.0f) && players.Position.x >= (-binPositions[0].x - 1.0f) && players.Position.z <= (-binPositions[0].z + 1.0f) && players.Position.z >= (-binPositions[0].z - 1.0f)) {
                int judge = 1;
                //CanModelMat = translate(CanModelMat,vec3(binPositions[0].x,garbagePositions[1].y,binPositions[0].z));
                //gloabl4 = translate(mat4(1.0f), binPositions[0]);
                //CanModel.GetPosition(vec3(binPositions[0].x-2.0f,0.0f,binPositions[0].z+3.0f));
                //CanModelMat = translate(CanModelMat, CanModel.position);
                CanModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
            else{
                int judge = 0;
                //gloabl4  = CanModelMat;
                //CanModelMat = translate(CanModelMat, garbagePositions[1]);
                //CanModel.GetPosition(garbagePositions[1]);
                CanModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (CanModel.pick == 0) {
                gloabl4  = CanModelMat;
            }
            else{
                gloabl4  = translate(mat4(1.0f), binPositions[0]);
                gloabl4 = scale(gloabl4, vec3(1.5f,1.5f,1.5f));
            }
        }
        
        CanShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(CanShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl4));
        glUniformMatrix4fv(glGetUniformLocation(CanShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(CanShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(CanShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(CanShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光

        glUniform3f(glGetUniformLocation(CanShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(CanShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(CanShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(CanShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(CanShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        CanMaterial->shader->SetUniform3f("material.ambient", CanMaterial->ambient);
        CanMaterial->shader->SetUniform1i("material.diffuse", 19);
        CanMaterial->shader->SetUniform1i("material.specular", 20);
        CanMaterial->shader->SetUniform1f("material.shininess", CanMaterial->shininess);
        CanModel.Draw(CanMaterial->shader);

        //Rose model
        mat4 gloabl5 = mat4(1.0f);
        RoseModelMat = translate(mat4(1.0f), garbagePositions[2]);
        RoseModelMat = rotate(RoseModelMat, radians(90.0f),vec3(0.0f, 1.0f, 0.0f));
        RoseModelMat = rotate(RoseModelMat, radians(90.0f),vec3(0.0f, 0.0f, 1.0f));
        RoseModelMat = scale(RoseModelMat, vec3(0.005f,0.005f,0.005f));
        if((players.pickNumber%2) == 1 && players.modelNumber == 3){
            gloabl5  = gloabl1 * RoseModelMat;
            RoseModel.PickState();
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 3){
            if (players.Position.x <= (-binPositions[3].x + 1.0f) && players.Position.x >= (-binPositions[3].x - 1.0f) && players.Position.z <= (-binPositions[3].z + 1.0f) && players.Position.z >= (-binPositions[3].z - 1.0f)) {
                int judge = 1;
                RoseModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
            else{
                int judge = 0;
                RoseModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (RoseModel.pick == 0) {
                gloabl5  = RoseModelMat;
            }
            else{
                gloabl5  = translate(mat4(1.0f), binPositions[3]);
                gloabl5 = rotate(gloabl5, radians(90.0f),vec3(0.0f, 1.0f, 0.0f));
                gloabl5 = rotate(gloabl5, radians(90.0f),vec3(0.0f, 0.0f, 1.0f));
                gloabl5 = scale(gloabl5, vec3(0.005f,0.005f,0.005f));
            }
        }
        RoseShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(RoseShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl5));
        glUniformMatrix4fv(glGetUniformLocation(RoseShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(RoseShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(RoseShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(RoseShader->ID,"ambientColor"),0.2f,0.0f,0.0f);//环境光

        glUniform3f(glGetUniformLocation(RoseShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(RoseShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(RoseShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(RoseShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(RoseShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        RoseMaterial->shader->SetUniform3f("material.ambient", RoseMaterial->ambient);
        RoseMaterial->shader->SetUniform1i("material.diffuse", 21);
        RoseMaterial->shader->SetUniform1i("material.specular", 22);
        RoseMaterial->shader->SetUniform1f("material.shininess", RoseMaterial->shininess);
        RoseModel.Draw(RoseMaterial->shader);
        
        //fish model
        mat4 gloabl6 = mat4(1.0f);
        fishModelMat = translate(mat4(1.0f), garbagePositions[3]);
        fishModelMat = rotate(fishModelMat, radians(90.0f),vec3(0.0f, 1.0f, 0.0f));
        fishModelMat = rotate(fishModelMat, radians(90.0f),vec3(0.0f, 0.0f, 1.0f));
        fishModelMat = scale(fishModelMat, vec3(0.25f,0.25f,0.25f));
        
        if((players.pickNumber%2) == 1 && players.modelNumber == 4){
            gloabl6 = gloabl1 * fishModelMat;
            fishModel.PickState();
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 4){
            if (players.Position.x <= (-binPositions[3].x + 1.0f) && players.Position.x >= (-binPositions[3].x - 1.0f) && players.Position.z <= (-binPositions[3].z + 1.0f) && players.Position.z >= (-binPositions[3].z - 1.0f)) {
                int judge = 1;
                fishModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
            else{
                int judge = 0;
                fishModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (fishModel.pick == 0) {
                gloabl6  = fishModelMat;
            }
            else{
                gloabl6  = translate(mat4(1.0f), binPositions[3]);
                gloabl6 = rotate(gloabl6, radians(90.0f),vec3(0.0f, 1.0f, 0.0f));
                gloabl6 = rotate(gloabl6, radians(90.0f),vec3(0.0f, 0.0f, 1.0f));
                gloabl6 = scale(gloabl6, vec3(0.25f,0.25f,0.25f));
            }
        }
        
        fishShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(fishShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl6));
        glUniformMatrix4fv(glGetUniformLocation(fishShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(fishShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(fishShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(fishShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
           
        glUniform3f(glGetUniformLocation(fishShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(fishShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(fishShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(fishShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(fishShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        fishMaterial->shader->SetUniform3f("material.ambient", fishMaterial->ambient);
        fishMaterial->shader->SetUniform1i("material.diffuse", 23);
        fishMaterial->shader->SetUniform1i("material.specular", 24);
        fishMaterial->shader->SetUniform1f("material.shininess", fishMaterial->shininess);
        fishModel.Draw(fishMaterial->shader);
        
        //Cup model
        mat4 gloabl7 = mat4(1.0f);
        CupModelMat = translate(mat4(1.0f), garbagePositions[4]);
        CupModelMat = scale(CupModelMat, vec3(0.05f,0.05f,0.05f));
        
        if((players.pickNumber%2) == 1 && players.modelNumber == 5){
            gloabl7  = gloabl1 * CupModelMat;
            CupModel.PickState();
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 5){
            if (players.Position.x <= (-binPositions[1].x + 1.0f) && players.Position.x >= (-binPositions[1].x - 1.0f) && players.Position.z <= (-binPositions[1].z + 1.0f) && players.Position.z >= (-binPositions[1].z - 1.0f)) {
                int judge = 1;
                CupModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
            else{
                int judge = 0;
                CupModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (CupModel.pick == 0) {
                gloabl7  = CupModelMat;
            }
            else{
                gloabl7  = translate(mat4(1.0f), binPositions[1]);
                gloabl7 = scale(gloabl7, vec3(0.05f,0.05f,0.05f));
            }
        }
        CupShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(CupShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl7));
        glUniformMatrix4fv(glGetUniformLocation(CupShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(CupShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(CupShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(CupShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
           
        glUniform3f(glGetUniformLocation(CupShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(CupShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(CupShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(CupShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(CupShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        CupMaterial->shader->SetUniform3f("material.ambient", CupMaterial->ambient);
        CupMaterial->shader->SetUniform1i("material.diffuse", 25);
        CupMaterial->shader->SetUniform1i("material.specular", 26);
        CupMaterial->shader->SetUniform1f("material.shininess", CupMaterial->shininess);
        CupModel.Draw(CupMaterial->shader);
        
        //Pill model
        mat4 gloabl8 = mat4(1.0f);
        PillModelMat = translate(mat4(1.0f), garbagePositions[5]);
        PillModelMat = scale(PillModelMat, vec3(0.0025f,0.0025f,0.0025f));
        
        if((players.pickNumber%2) == 1 && players.modelNumber == 6){
            gloabl8  = gloabl1 * PillModelMat;
            PillModel.PickState();
        }
        else if((players.pickNumber%2) == 0 && players.modelNumber == 6){
            if (players.Position.x <= (-binPositions[2].x + 1.0f) && players.Position.x >= (-binPositions[2].x - 1.0f) && players.Position.z <= (-binPositions[2].z + 1.0f) && players.Position.z >= (-binPositions[2].z - 1.0f)) {
                int judge = 1;
                PillModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
            else{
                int judge = 0;
                PillModel.PutState(judge);
                players.modelNumber = 0;
                players.Draw(judge);
            }
        }
        else{
            if (PillModel.pick == 0) {
                gloabl8  = PillModelMat;
            }
            else{
                gloabl8  = translate(mat4(1.0f), vec3(binPositions[2].x,-1.9f,binPositions[2].z));
                gloabl8 = scale(gloabl8, vec3(0.0025f,0.0025f,0.0025f));
            }
        }
        PillShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(PillShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl8));
        glUniformMatrix4fv(glGetUniformLocation(PillShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(PillShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(PillShader->ID,"objColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(PillShader->ID,"ambientColor"),0.1f,0.1f,0.1f);//环境光
           
        glUniform3f(glGetUniformLocation(PillShader->ID,"lightD.pos"),light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(PillShader->ID,"lightD.color"),light.color.x,light.color.y,light.color.z);
        glUniform3f(glGetUniformLocation(PillShader->ID,"lightD.dirToLight"),light.direction.x,light.direction.y,light.direction.z);
        glUniform1i(glGetUniformLocation(PillShader->ID,"shadowMap"),0);
        glUniform3f(glGetUniformLocation(PillShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        PillMaterial->shader->SetUniform3f("material.ambient", PillMaterial->ambient);
        PillMaterial->shader->SetUniform1i("material.diffuse", 27);
        PillMaterial->shader->SetUniform1i("material.specular", 28);
        PillMaterial->shader->SetUniform1f("material.shininess", PillMaterial->shininess);
        PillModel.Draw(PillMaterial->shader);
        
        //cube1.Draw(cube1Material->shader);
        
        //Clean up,prepare for next render loop
        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents(); //用户的按键获取,需要时间
        camera.UpdateCameraPos();
        //players.UpdatePlayerPos();
    }
    //Exit Program
    glfwTerminate();
    return 0; //正常
    }
