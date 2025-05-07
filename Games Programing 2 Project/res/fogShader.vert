#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 modelMatrix;
uniform mat4 transform;
uniform vec3 camPos;

out vec3 v_norm;
out vec4 v_pos; 
out vec2 tC;

void main()
{
	tC = TextCoords;
	v_norm = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
	vec4 worldPosition = transform * vec4(VertexPosition, 1.0);
	v_pos = vec4(worldPosition.xyz - camPos, 1.0);
	gl_Position = transform * vec4(VertexPosition, 1.0);
}