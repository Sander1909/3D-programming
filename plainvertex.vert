#version 330
layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
layout(location = 2) in vec2 uv;
out vec4 col;
uniform mat4 matrix;

void main() {
   col = colAttr;
//   col.r += uv.x;   //nonsence, just to use the variable
//   col.g += uv.y;   //not using a variable in a shader sometimes gives errors/warnings
   gl_Position = matrix * posAttr;
}
