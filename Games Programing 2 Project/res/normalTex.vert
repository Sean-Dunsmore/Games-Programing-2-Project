#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;

out vec2 tC;
out vec3 normal;

uniform mat4 modelMatrix;

void main()
{
    tC = TextCoords;
    normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
    gl_Position = transform * vec4(VertexPosition, 1.0);

}