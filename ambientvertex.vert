#version 330
layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
layout(location = 2) in vec2 uv;
out vec4 vertexColor;
uniform mat4 matrix;

void main() {
   vertexColor = colAttr;
   gl_Position = matrix * posAttr;
}
