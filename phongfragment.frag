#version 330

out vec4 fragColor;
in vec4 vertexColor;
in vec4 fragPos;

uniform vec4 ambientColor;
uniform vec4 lightPos;
uniform vec3 cameraPos;


void main() {

    vec4 lightCol = vec4(1.f,1.f,1.f,1.f);
    vec4 lightDir = normalize(lightPos - fragPos);

    float specularStrength = 0.5f;
    vec4 viewDir = normalize(vec4(cameraPos,1.f)- fragPos);
    vec4 reflectDir = reflect(-lightDir, vertexColor);
    float spec = pow(max(dot(viewDir, reflectDir),0.f),32);
    vec4 specular = specularStrength * spec * lightCol;


    float diff = max(dot(vertexColor, lightDir),0.f);
    vec4 diffuse = diff * lightCol;
    vec4 result = (ambientColor + diffuse + specular) * vec4 (0.3f,0.3f,0.3f,1.f);

    fragColor = result;
}
