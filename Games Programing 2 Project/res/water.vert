#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;

out vec2 tC;
out float time;
uniform mat4 transform;
uniform float counter;
uniform float height;
uniform float width;

void main()
{
	tC = TextCoords;
	time = counter;
	vec3 alteredVertex = vec3(VertexPosition.x,VertexPosition.y + (height * sin(abs(width * VertexPosition.x + counter))),VertexPosition.z);
	gl_Position = transform * vec4(alteredVertex, 1.0);
}