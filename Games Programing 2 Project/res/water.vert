#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextCoords;

out vec2 tC; //Text coordinates
out float time; //Float representing time passed
uniform mat4 transform;
uniform float counter;  //Float representing time passed
uniform float height;  //Height of waves
uniform float width; //Width of waves

void main()
{
	tC = TextCoords;
	time = counter;
	//Alter vertexs to form waves using a sine function
	vec3 alteredVertex = vec3(VertexPosition.x,VertexPosition.y + (height * sin(abs(width * VertexPosition.x + counter))),VertexPosition.z);
	gl_Position = transform * vec4(alteredVertex, 1.0);
}