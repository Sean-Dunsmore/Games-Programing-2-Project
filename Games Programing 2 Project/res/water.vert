#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;

out vec2 tC;
out float time;
uniform mat4 transform;
uniform float counter;

void main()
{
	tC = TextCoords;
	time = counter;
	vec3 alteredVertex = vec3(VertexPosition.x,VertexPosition.y + (20 * sin(abs(VertexPosition.x + counter))),VertexPosition.z);
	gl_Position = transform * vec4(alteredVertex, 1.0);
}