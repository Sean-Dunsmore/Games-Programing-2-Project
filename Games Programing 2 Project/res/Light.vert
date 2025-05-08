#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 VertexNormal;

out vec3 normal; //Normals
out vec2 tC; //Tex coords
out vec3 viewDirection; //direction camera is facing
out vec3 position; //World position

uniform mat4 modelMatrix;
uniform mat4 transform;
uniform vec3 camPos; //Camera position

void main()
{
	tC = TextCoords;
	normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
	vec4 worldPosition = transform * vec4(VertexPosition, 1.0);
	position = vec3(modelMatrix * vec4(VertexPosition, 1.0));
	vec4 viewPosition = vec4(worldPosition.xyz - camPos, 1.0);
	viewDirection = -vec3(viewPosition);
	gl_Position = transform * vec4(VertexPosition, 1.0);
}