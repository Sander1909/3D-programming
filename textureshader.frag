#version 330

in vec2 UV;
uniform sampler2D textureSampler1;
uniform sampler2D textureSampler2;
out vec3 fragColor;

void main() {

    vec3 hund = texture( textureSampler1, UV ).rgb;
    vec3 uvMal = texture( textureSampler2, UV ).rgb;

   fragColor = mix(hund, uvMal, 0.5);
}

//#version 330 core

//// Interpolated values from the vertex shaders
//in vec2 UV;

//// Ouput data
//out vec3 color;

// Values that stay constant for the whole mesh.
//uniform sampler2D myTextureSampler;

//void main(){

//    // Output color = color of the texture at the specified UV
//    color = texture( myTextureSampler, UV ).rgb;
