#version 330 core

// Ouput data
//out vec4 color;
out uvec3 FragColor;
// Values that stay constant for the whole mesh.
//uniform vec4 PickingColor;
uniform uint gDrawIndex;
uniform uint gObjectIndex;
void main(){
    
    //color = PickingColor;
    FragColor = uvec3(gObjectIndex, gDrawIndex,gl_PrimitiveID + 1);

}
