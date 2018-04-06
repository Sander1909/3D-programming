#version 330
in vec4 vertexColor;

out vec4 fragColor;

uniform vec3 ambientColor;
uniform float lightStrength;

void main()
{
    fragColor = vertexColor * vec4(ambientColor, 1.f) * lightStrength;
}
