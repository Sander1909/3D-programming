#version 330

in vec4 vertexColor;
in vec4 fragPosition;

out vec4 fragColor;

uniform vec4 ambientColor;
uniform vec4 lightPosition;
uniform vec3 cameraPosition;


void main() {

    vec4 lightCol = vec4(1.f,1.f,1.f,1.f);
    vec4 lightDir = normalize(lightPosition - fragPosition);

    float specularStrength = 0.5f;
    vec4 viewDir = normalize(vec4(cameraPosition,1.f)- fragPosition);

    vec4 reflectDir = reflect(-lightDir, vertexColor);
    float spec = pow(max(dot(viewDir, reflectDir),0.f),32);
    vec4 specular = specularStrength * spec * lightCol;

    float diff = max(dot(vertexColor, lightDir),0.f);
    vec4 diffuse = diff * lightCol;
    vec4 result = (ambientColor + diffuse + specular) * vec4 (0.4f,0.4f,0.4f,1.f);

    fragColor = result;
}
