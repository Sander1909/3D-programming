#version 330
layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
layout(location = 2) in vec2 vertexUV;

out vec4 col;
out vec2 UV;
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main() {
   col = colAttr;
   gl_Position = pMatrix * vMatrix * mMatrix * posAttr; //pMatrix * vMatrix  *mMatrix
   UV = vertexUV;
}


//#version 330 core

// Input vertex data, different for all executions of this shader.
//layout(location = 0) in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
//out vec2 UV;

// Values that stay constant for the whole mesh.
//uniform mat4 MVP;

//void main(){

//    // Output position of the vertex, in clip space : MVP * position
//    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

//    // UV of the vertex. No special space for this one.
//    UV = vertexUV;
//}
