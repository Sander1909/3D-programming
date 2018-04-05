#version 330
layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
layout(location = 2) in vec2 uv;
out vec4 vertexColor;
out vec4 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
   vertexColor = colAttr;
   mat4 matrix = projection * view * model;
   gl_Position = matrix * posAttr;
   fragPos = model * posAttr;
}
